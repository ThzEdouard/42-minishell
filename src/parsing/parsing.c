/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:28 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/15 13:15:36 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_init(t_list_token *l)
{
	l->first = NULL;
	l->last = NULL;
}

void	token_pusht_(t_list_token *l, int val, char *str)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->space = val;
	new->str = str;
	new->prev = l->last;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
}

void	pars_cmd(t_list_token *l, char *line)
{
	
}

int	parsing(char *line)
{
	return (SUCCESS);
}