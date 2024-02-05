/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:50:41 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/11 20:02:03 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_size_env(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->str)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->str)
			ft_putendl_fd(tmp->str, 1);
		tmp = tmp->next;
	}
	g_statesssss = 0;
	return (0);
}
