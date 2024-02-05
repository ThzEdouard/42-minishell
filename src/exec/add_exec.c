/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:24:03 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 21:06:29 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec	*add_exec(t_token *t, t_env *env)
{
	t_list_exec	exec;
	t_add		values;
	t_token		*tmp;

	tmp = t;
	add_exec_init(&exec, &values);
	if (malloc_cmd_filename(tmp, &values))
		return (NULL);
	while (tmp)
	{
		if (tmp->type == WORD)
			cmd_word(&exec, tmp, &values, env);
		else if (tmp->type == WRITE || tmp->type == APPEND)
			tmp = write_append(&exec, tmp, &values, env);
		else if (tmp->type == READ || tmp->type == HEREDOC)
			tmp = read_heredoc(&exec, tmp, &values, env);
		if ((tmp && tmp->next) || tmp)
			tmp = tmp->next;
	}
	free_add_exec(values);
	return (exec.first);
}

void	free_add_exec(t_add values)
{
	if (values.filename)
		free(values.filename);
	if (values.command)
		free(values.command);
	if (values.type)
		free(values.type);
}

char	**new_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	envp = malloc(sizeof(char *) * (ft_size_env(env) + 1));
	if (!envp)
		return (NULL);
	envp[ft_size_env(env)] = NULL;
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->str)
			envp[i] = tmp->str;
		i++;
		tmp = tmp->next;
	}
	return (envp);
}
