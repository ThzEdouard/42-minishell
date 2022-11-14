/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:32:45 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/14 23:42:21 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_ralou(char *s, int i, int y, int len, char *s2)
{
	char *r = malloc(sizeof(char *) *(i - y + len));
	if (!r)
		return (s);
	int	x = 0;
	while (x != y - 1)
	{
		r[x] = s[x];
		x++;
	}
	if (s2)
	{
		char *e = ft_strdup(s2 + (i - y + 1));
		int o = 1;
		while (e[o])
		{
			r[x] = e[o];
			x++;
			o++;
		}
	}
	int p = 0;
	while (p != y - 1)
		p++;
	int t = i - y;
	while (t)
		p++, t--;
	while (s[p])
	{
		r[x] = s[p];
		x++, p++;
	}
	r[x] = 0;
	return (r);
}

void	ta_mere(t_list_token *l, t_env *env)
{
	int	i;
	int y;
	int x = 0;
	t_token *tmp;
	tmp = l->first;
	while (tmp)
	{
		i = 0;
		y = 0;
		x = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] && i == 0 && tmp->str[i] == 39)
				break ;
			if (tmp->str[i] && tmp->str[i] == 36)
			{
				i++;
				y = i;
				while (tmp->str[i] && tmp->str[i] != 34 && tmp->str[i] != 39 && tmp->str[i] != 32)
					i++, x++;
			}
			if (x != 0)
				break ;
			i++;
		}
		if (x != 0)
		{
			char *t = get_name(env, tmp->str + y, x);
			if (!t)
				continue ;
			char * zozo = ft_ralou(tmp->str, i, y, ft_strlen(t), t);
			free (tmp->str);
			tmp->str = zozo;
		}
		tmp = tmp->next;
	}
}
