/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:06:42 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/06 17:11:59 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_init(t_list_token *l)
{
	l->first = NULL;
	l->last = NULL;
}

int	add_list(t_list_token *l, char *line, int end)
{
	char	*str;

	str = ft_substr(line, 0, end);
	if (!str)
		return (FAIL);
	if (token_push(l, str))
		return (FAIL);
	return (SUCCESS);
}

int	token_push(t_list_token *l, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (FAIL);
	new->str = str;
	new->prev = l->last;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
	return (SUCCESS);
}

void	view(t_list_token l)
{
	t_token	*pelem;

	pelem = l.first;
	printf("===========================\n");
	while (pelem)
	{
		printf("str {%s} type {%d}\n", pelem->str, pelem->type);
		pelem = pelem->next;
	}
	printf("==============================\n");
}

void	token_clear(t_list_token *l)
{
	t_token	*tmp;
	t_token	*elem;

	if (!l->first)
		return ;
	elem = l->first;
	while (elem)
	{
		tmp = elem;
		if (tmp->str)
			free(tmp->str);
		tmp->str = NULL;
		elem = elem->next;
		free(tmp);
	}
	l->first = NULL;
	l->last = NULL;
}
