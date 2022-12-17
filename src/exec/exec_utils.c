/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 03:11:35 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/17 21:59:39 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_all(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	exec_push_v2(t_list_exec *l, char **cmd, char **filename, t_type *type)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	exec_push_v2_2(new, cmd, filename, type);
	new->path_cmd = NULL;
	new->file = NULL;
	new->fileproblem = 0;
	new->saveout = dup(STDOUT_FILENO);
	new->savein = dup(STDIN_FILENO);
	new->prev = l->last;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
}

void	exec_push_v2_2(t_exec *new, char **cmd, char **filename, t_type *type)
{
	if (cmd)
		new->cmd = ft_double_realloc(cmd);
	else
		new->cmd = NULL;
	if (filename)
		new->filename = ft_double_realloc(filename);
	else
		new->filename = NULL;
	if (type)
		new->type = ft_double_realloc_enum(type);
	else
		new->type = NULL;
}

void	exec_clear(t_list_exec *l)
{
	t_exec	*tmp;
	t_exec	*elem;

	elem = l->first;
	while (elem)
	{
		tmp = elem;
		if (!ft_check_builtins(tmp))
		{
			close(tmp->pipefd[0]);
			close(tmp->pipefd[1]);
		}
		if (tmp->cmd && tmp->cmd[0] == tmp->path_cmd)
			ft_free_all(tmp->cmd);
		else
		{
			ft_free_all(tmp->cmd);
			if (tmp->path_cmd)
				free(tmp->path_cmd);
		}
		tmp->path_cmd = NULL;
		ft_free_all(tmp->filename);
		if (tmp->file)
			free(tmp->file);
		if (elem->type)
			free(elem->type);
		close(tmp->savein);
		close(tmp->saveout);
		elem = elem->next;
		free(tmp);
	}
	exec_clear_reset(l);
}

void	exec_clear_reset(t_list_exec *l)
{
	l->first = NULL;
	l->last = NULL;
}
