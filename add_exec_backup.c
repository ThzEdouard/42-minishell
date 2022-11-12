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
	int			i;
	int			y;
	int			j;
	int			nb_filename = 0;
	int			nb_cmd = 0;
	t_list_exec exec;
	t_token 	*tmp;
	char		**command;
	char		**filename;

	i = 0;
	y = 0;
	j = 0;
	tmp = t;
	exec_init(&exec);

	while(tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE)
		{
			nb_filename++;
		}
		if (tmp->type == WORD)
		{
			nb_cmd++;
		}
		// printf("%d     ", tmp->type);
		tmp = tmp->next;
	}
	nb_cmd -= nb_filename;
	printf("nb_filename: %d | nb_cmd: %d\n", nb_filename, nb_cmd);

	// filename = malloc(sizeof(char *) * nb_filename + 1);
	// command = malloc(sizeof(char *) * nb_cmd  + 1 );
	filename = malloc(10000);
	command = malloc(10000);

	while (t)
	{
		if (t->type == WORD)
		{
			command[y] = t->str;
			y++;
			if (!(t->next) || t->next->type == PIPE || t->type == PIPE)
			{
				command[y] = 0;
				exec_push(&exec, command, filename, WORD);
				exec.first = set_path(exec.first, env);
				i = 0;
				while(command[i])
				{
					command[i] = 0;
					i++;
				}
				i = 0;
				y = 0;
			}
		}

		else if (t->type == WRITE)
		{
			j = 0;
			filename[j++] = t->next->str;
			while(t->next->next && t->next->next->type == WRITE)
			{
				t = t->next->next;
				filename[j] = t->next->str;
				j++;
			}
			exec_push(&exec, command, filename, WRITE);
			exec.first = set_path(exec.first, env);
			j = 0;
			while(filename[j])
			{
				filename[j] = 0;
				j++;
			}
			i = 0;
			y = 0;
			t = t->next;
		}

		else if (t->type == APPEND)
		{
			j = 0;
			filename[j++] = t->next->str;
			while(t->next->next && t->next->next->type == WRITE)
			{
				t = t->next->next;
				filename[j] = t->next->str;
				j++;
			}
			exec_push(&exec, command, filename, APPEND);
			exec.first = set_path(exec.first, env);
			j = 0;
			while(filename[j])
			{
				filename[j] = 0;
				j++;
			}
			i = 0;
			y = 0;
			t = t->next;
		}

		else if (t->type == READ)
		{
			j = 0;
			filename[j++] = t->next->str;
			while(t->next->next && t->next->next->type == WRITE)
			{
				t = t->next->next;
				filename[j] = t->next->str;
				j++;
			}
			while (t->next->next && t->next->next->type == WORD)
			{
				command[y] = t->next->next->str;
				y++;
				t = t->next;
			}
			exec_push(&exec, command, filename, READ);
			exec.first = set_path(exec.first, env);
			j = 0;
			while(filename[j])
			{
				filename[j] = 0;
				j++;
			}
			i = 0;
			y = 0;
			t = t->next;
		}


		else if (t->type == HEREDOC)
		{
			j = 0;
			filename[j++] = t->next->str;
			while(t->next->next && t->next->next->type == HEREDOC)
			{
				t = t->next->next;
				filename[j] = t->next->str;
				j++;
			}
			while (t->next->next && t->next->next->type == WORD)
			{
				command[y] = t->next->next->str;
				y++;
				t = t->next;
			}
			exec_push(&exec, command, filename, HEREDOC);
			exec.first = set_path(exec.first, env);
			j = 0;
			while(filename[j])
			{
				filename[j] = 0;
				j++;
			}
			i = 0;
			y = 0;
			t = t->next;
		}
		t = t->next;

	}
	// free(command);
	// free(filename);
	return (exec.first);
}