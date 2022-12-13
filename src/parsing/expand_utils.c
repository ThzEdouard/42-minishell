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
	if (tmp->str[a] && tmp->str[a] == 36)
		a++;
	*tmp1 = a + 1;
	if (tmp->str[a] != 36)
		while (tmp->str[a] && tmp->str[a] != 34 && tmp->str[a]
			!= 39 && tmp->str[a] != 32 && tmp->str[a] != 36)
				a++;
	else
		a++;
	*i = a;
}

void	test_expand(t_token *tmp, t_env *env)
{
	int		i;
	int		tmp1;

	i = 0;
	while (tmp && tmp->str[i] && tmp->trace == YES)
	{
		if (tmp->str[i] == 39)
		{
			i++;
			while (tmp->str[i] && tmp->str[i] != 39)
				i++;
		}
		if (tmp->str[i] && tmp->str[i] == 36)
		{
			expand_process(tmp, &tmp1, &i);
			if (!tmp->str[tmp1 - 1])
				break ;
			//printf("1291540");
			if (/*tmp->str[i - 1] != 36 ||*/ (tmp->str[i] != 34
					&& tmp->str[i] != 39))
					{
						update_str(&tmp->str, env, i, tmp1);
					}
			if (i != tmp1)
				i = tmp1 - 1;
			else
				i++;
		}
		printf("\ni  = %d\n", i);
		if (tmp->str[i])
			i++;
	}
}

int	expand_utils(t_list_token *l, t_env *env)
{
	t_token	*tmp;

	tmp = l->first;
	while (tmp)
	{
		test_expand(tmp, env);
		if (tmp)
			tmp = tmp->next;
	}
	return (SUCCESS);
}
