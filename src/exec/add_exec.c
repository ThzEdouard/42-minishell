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

	values.i = 0;
	values.y = 0;
	values.j = 0;
	tmp = t;
	exec_init(&exec);
	malloc_cmd_filename(tmp, &values);
	while (tmp)
	{
		if (tmp->type == WORD)
			cmd_word(&exec, tmp, &values, env);
		else if (tmp->type == WRITE)
			tmp = cmd_write(&exec, tmp, &values, env);
		else if (tmp->type == APPEND)
			tmp = cmd_append(&exec, tmp, &values, env);
		else if (tmp->type == READ)
			tmp = cmd_read(&exec, tmp, &values, env);
		else if (tmp->type == HEREDOC)
			tmp = cmd_here(&exec, tmp, &values, env);
		tmp = tmp->next;
	}
	return (exec.first);
}

void	calcul_len_malloc(t_token *tmp, int *len_cmd, int *len_file)
{
	int	file;
	int	cmd;

	file = 0;
	cmd = 0;
	while (tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE)
		{
			file++;
		}
		else if (tmp->type == WORD)
		{
			cmd++;
		}
		tmp = tmp->next;
	}
	cmd -= file;
	*len_cmd = cmd;
	*len_file = file;
}

void	malloc_cmd_filename(t_token *t, t_add *values)
{
	int	nb_filename;
	int	nb_cmd;

	nb_filename = 0;
	nb_cmd = 0;
	calcul_len_malloc(t, &nb_cmd, &nb_filename);
	// printf("nb_filename: %d | nb_cmd: %d\n", nb_filename, nb_cmd);
	values->filename = malloc(sizeof(char *) * nb_filename + 1);
	values->command = malloc(sizeof(char *) * nb_cmd + 1);
	values->filename[0] = 0;
	values->command[0] = 0;
}
