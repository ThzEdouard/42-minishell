/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:01:26 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/02 22:30:45 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//a finir !
void	exec_init(t_list_exec *l)
{
	l->first = NULL;
	l->first = NULL;
}

static char *ft_acces(t_list_exec *l)
{

}

static char	**ft_path(t_list_exec *l, t_env *env)
{
	return (NULL);
}

void	exec_push(t_list_exec *l, char **cmd, char **filename, t_env *env)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return ;
	new->cmd = cmd;
	new->path_cmd = ft_path();
	new->file->filename = filename;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
}

void	exec_clear()
{

}