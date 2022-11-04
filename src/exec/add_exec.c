/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:24:03 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 18:09:28 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec	*add_exec(t_token *t)
{
	int		i;
	int		y;
	int	j;
	t_list_exec exec;

	char	**command;
	char	**filename;

	i = 0;
	y = 0;
	j = 0;
	exec_init(&exec);
	filename = malloc(10000);
	command = malloc(10000);

	while (t)
	{
		if (t->type == WORLD)
		{
			command[y] = t->str;
			y++;
			if (!(t->next) || t->next->type == PIPE || t->type == PIPE)
			{
				exec_push(&exec, command, filename, WORLD, NULL);
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
			exec_push(&exec, command, filename, WRITE, NULL);
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
			exec_push(&exec, command, filename, APPEND, NULL);
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
			while (t->next->next && t->next->next->type == WORLD)
			{
				command[y] = t->next->next->str;
				y++;
				t = t->next;
			}
			exec_push(&exec, command, filename, READ, NULL);
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
			while (t->next->next && t->next->next->type == WORLD)
			{
				command[y] = t->next->next->str;
				y++;
				t = t->next;
			}
			exec_push(&exec, command, filename, HEREDOC, NULL);
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
	return (exec.first);
}