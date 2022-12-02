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
		else if (tmp->type == READ)
			tmp = cmd_read(&exec, tmp, &values, env);
		else if (tmp->type == HEREDOC)
			tmp = cmd_here(&exec, tmp, &values, env);
		tmp = tmp->next;
	}
	if (values.filename)
		free(values.filename);
	if (values.command)
		free(values.command);
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

int	malloc_cmd_filename(t_token *t, t_add *values)
{
	int	nb_filename;
	int	nb_cmd;

	nb_filename = 0;
	nb_cmd = 0;
	calcul_len_malloc(t, &nb_cmd, &nb_filename);
	if (malloc_command(values, nb_cmd))
		return (FAIL);
	if (!values->filename && nb_filename)
	{
		values->filename = malloc(sizeof(char *) * (nb_filename + 1));
		values->type = malloc(sizeof(t_type) * (nb_filename + 1));
		if (!values->filename)
			return (FAIL);
		while (nb_filename)
		{
			values->filename[nb_filename] = 0;
			values->type[nb_filename--] = 0;
		}
	}
	malloc_type(values);
	return (SUCCESS);
}

int	malloc_command(t_add *values, int nb_cmd)
{
	if (!values->command && nb_cmd)
	{
		values->command = malloc(sizeof(char *) * (nb_cmd + 1));
		if (!values->command)
			return (FAIL);
		while (nb_cmd)
			values->command[nb_cmd--] = 0;
	}
	return (SUCCESS);
}

void	malloc_type(t_add *values)
{
	if (!values->type)
	{
		values->type = malloc(sizeof(t_type) * 1);
		values->type[0] = 0;
	}
}
