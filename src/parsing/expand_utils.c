/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:32:45 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/15 22:16:25 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_process(t_token *tmp, int *tmp1, int *i)
{
	int	a;

	a = *i;
	while (tmp->str[a] && tmp->str[a] == 36)
		a++;
	*tmp1 = a + 1;
	while (tmp->str[a] && tmp->str[a] != 34 && tmp->str[a]
		!= 39 && tmp->str[a] != 32 && tmp->str[a] != 36)
		a++;
	*i = a;
}

int	expand_utils(t_list_token *l, t_env *env)
{
	t_token	*tmp;
	int		i;
	int		tmp1;

	tmp = l->first;
	while (tmp)
	{
		i = 0;
		while (tmp->str[i])
		{
			if (i == 0 && tmp->str[i] == 39)
				break ;
			if (tmp->str[i] && tmp->str[i] == 36)
			{
				expand_process(tmp, &tmp1, &i);
				update_str(&tmp->str, env, i, tmp1);
				i = tmp1;
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
