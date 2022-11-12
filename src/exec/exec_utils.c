/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 03:11:35 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/12 21:23:00 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_init(t_list_exec *l)
{
	l->first = NULL;
	l->last = NULL;
}

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
}

void	exec_push(t_list_exec *l, char **cmd, char **filename, e_type type)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return ;
	printf("cmd: %s | filename: %s | type: %d\n", cmd[0], filename[0], type);
	new->cmd = ft_double_raloc(cmd);
	new->filename = ft_double_raloc(filename);
	new->path_cmd = NULL;
	new->file = NULL;
	new->type = type;
	new->prev = l->last;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
}

void	exec_clear(t_list_exec *l)
{
	t_exec	*tmp;
	t_exec	*elem;

	elem = l->first;
	while (elem)
	{
		tmp = elem;
		ft_free_all(tmp->cmd);
		if (tmp->path_cmd)
			free(tmp->path_cmd);
		ft_free_all(tmp->filename);
		if (tmp->file)
			free(tmp->file);
		elem = elem->next;
		free(tmp);
	}
	l->first = NULL;
	l->last = NULL;
}
