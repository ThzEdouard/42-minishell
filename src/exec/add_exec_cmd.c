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
	values->command[values->y] = t->str;
	values->y++;
	if (!(t->next) || t->next->type == PIPE || t->type == PIPE)
	{
		values->command[values->y] = 0;
		exec_push(exec, values->command, values->filename, WORD);
		exec->first = set_path(exec->first, env);
		values->i = 0;
		while (values->command[values->i])
		{
			values->command[values->i] = 0;
			values->i++;
		}
		values->i = 0;
		values->y = 0;
	}
}

t_token	*cmd_write(t_list_exec *exec, t_token *t, t_add *values, t_env *env)
{
	values->j = 0;
	values->filename[values->j++] = t->next->str;
	while (t->next->next && t->next->next->type == WRITE)
	{
		t = t->next->next;
		values->filename[values->j++] = t->next->str;
	}
	values->filename[values->j] = 0;
	exec_push(exec, values->command, values->filename, WRITE);
	exec->first = set_path(exec->first, env);
	values->j = 0;
	while (values->filename[values->j])
		values->filename[values->j++] = 0;
	values->i = 0;
	values->y = 0;
	return (t->next);
}

t_token	*cmd_append(t_list_exec *exec, t_token *t, t_add *values, t_env *env)
{
	values->j = 0;
	values->filename[values->j++] = t->next->str;
	while (t->next->next && t->next->next->type == WRITE)
	{
		t = t->next->next;
		values->filename[values->j++] = t->next->str;
	}
	values->filename[values->j] = 0;
	exec_push(exec, values->command, values->filename, APPEND);
	exec->first = set_path(exec->first, env);
	values->j = 0;
	while (values->filename[values->j])
		values->filename[values->j++] = 0;
	values->i = 0;
	values->y = 0;
	return (t->next);
}

t_token	*cmd_read(t_list_exec *exec, t_token *t, t_add *values, t_env *env)
{
	values->j = 0;
	values->filename[values->j++] = t->next->str;
	while (t->next->next && t->next->next->type == WRITE)
	{
		t = t->next->next;
		values->filename[values->j++] = t->next->str;
	}
	while (t->next->next && t->next->next->type == WORD)
	{
		values->command[values->y++] = t->next->next->str;
		t = t->next;
	}
	values->filename[values->j] = 0;
	values->command[values->y] = 0;
	exec_push(exec, values->command, values->filename, READ);
	exec->first = set_path(exec->first, env);
	values->j = 0;
	while (values->filename[values->j])
		values->filename[values->j++] = 0;
	values->i = 0;
	values->y = 0;
	return (t->next);
}

t_token	*cmd_here(t_list_exec *exec, t_token *t, t_add *values, t_env *env)
{
	values->j = 0;
	values->filename[values->j++] = t->next->str;
	while (t->next->next && t->next->next->type == HEREDOC)
	{
		t = t->next->next;
		values->filename[values->j++] = t->next->str;
	}
	while (t->next->next && t->next->next->type == WORD)
	{
		values->command[values->y++] = t->next->next->str;
		t = t->next;
	}
	values->command[values->y] = 0;
	values->filename[values->j] = 0;
	exec_push(exec, values->command, values->filename, HEREDOC);
	exec->first = set_path(exec->first, env);
	values->j = 0;
	while (values->filename[values->j])
		values->filename[values->j++] = 0;
	values->i = 0;
	values->y = 0;
	return (t->next);
}
