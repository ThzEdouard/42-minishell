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

void	cmd_word(t_list_exec *exec, t_token *t, t_add *values, t_env *env)
{
	values->y = 0;
	values->command[values->y++] = t->str;
	if (!(t->next) || t->next->type == PIPE || t->type == PIPE)
	{
		values->command[values->y] = 0;
		values->type[0] = WORD;
		values->type[1] = 0;
		exec_push_v2(exec, values->command, values->filename, values->type);
		exec->first = set_path(exec->first, env);
		values->i = 0;
		if (values->command)
		{
			while (values->command[values->i])
				values->command[values->i++] = 0;
		}
		values->i = 0;
		values->y = 0;
	}
}

t_token	*write_append(t_list_exec *exec, t_token *t, t_add *values, t_env *env)
{
	values->filename[values->j] = t->next->str;
	values->type[values->j++] = t->type;
	while (t->next->next && (t->next->next->type == WRITE
			|| t->next->next->type == APPEND))
	{
		t = t->next->next;
		values->filename[values->j] = t->next->str;
		values->type[values->j++] = t->type;
	}
	values->filename[values->j] = 0;
	values->type[values->j] = 0;
	exec_push_v2(exec, values->command, values->filename, values->type);
	exec->first = set_path(exec->first, env);
	values->j = 0;
	while (values->filename[values->j])
		values->filename[values->j++] = 0;
	if (values->command)
		while (values->command[values->i])
			values->command[values->i++] = 0;
	values->i = 0;
	while (values->type[values->i])
		values->type[values->i++] = 0;
	values->i = 0;
	values->j = 0;
	return (t->next);
}

t_token	*read_heredoc(t_list_exec *exec, t_token *t, t_add *values, t_env *env)
{
	while (t->next && t->next->type != PIPE
		&& t->next->type != WRITE && t->next->type != APPEND)
	{
		if (t->next && t->next->type == WORD)
		{
			values->filename[values->j] = t->next->str;
			values->type[values->j++] = t->type;
			t = t->next;
		}
		while (t->next && (t->next->type != READ && t->next->type != HEREDOC
				&& t->next->type != PIPE && t->next->type != WRITE
				&& t->next->type != APPEND))
		{
			values->command[values->y++] = t->next->str;
			t = t->next;
		}
		if (t->next && t->next->type != PIPE
			&& t->next->type != WRITE && t->next->type != APPEND)
			t = t->next;
	}
	read_heredoc_2(exec, values, env);
	return (t);
}

void	read_heredoc_2(t_list_exec *exec, t_add *values, t_env *env)
{
	values->filename[values->j] = 0;
	values->type[values->j] = 0;
	if (values->command)
		values->command[values->y] = 0;
	exec_push_v2(exec, values->command, values->filename, values->type);
	exec->first = set_path(exec->first, env);
	values->j = 0;
	while (values->filename[values->j])
		values->filename[values->j++] = 0;
	values->y = 0;
	values->j = 0;
}
