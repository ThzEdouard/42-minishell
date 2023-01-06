/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:53:05 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/06 13:08:22 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	delete_quote(t_token *tmp, int i, char c)
{
	int	x;
	int	y;

	c = tmp->str[i];
	y = i;
	if (tmp->str[i] && tmp->str[i] == c)
		i++;
	while (tmp->str[i] && tmp->str[i] != c)
	{
		tmp->str[y] = tmp->str[i];
		y++;
		i++;
	}
	if (tmp->str[i] && tmp->str[i] == c)
		i++;
	x = i;
	while (tmp->str[x])
	{
		tmp->str[y] = tmp->str[x];
		y++;
		x++;
	}
	tmp->str[y] = tmp->str[x];
	i -= 2;
	return (i);
}

void	extand(t_token *t)
{
	t_token	*tmp;
	int		i;
	char	c;

	tmp = t;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			c = 0;
			while (tmp->str[i] && (tmp->str[i] != 34 && tmp->str[i] != 39))
				i++;
			if (tmp->str[i] && (tmp->str[i] == 34 || tmp->str[i] == 39))
				i = delete_quote(tmp, i, c);
		}
		tmp = tmp->next;
	}
}
