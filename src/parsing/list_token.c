/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:20:02 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/15 13:20:29 by eflaquet         ###   ########.fr       */
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

	str = ft_substr(line - end, 0, end);
	printf("str =  %s\n", str);
	if (!str)
		return (FAIL);
	token_push(l, str);
	return (SUCCESS);
}

void	token_push(t_list_token *l, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->str = str;
	new->prev = l->last;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
	printf("new str = %s\n", new->str);
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
