/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 05:43:01 by aradice           #+#    #+#             */
/*   Updated: 2022/11/10 05:43:01 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	checking_args(char **cmd, int *t, int i)
{
	int	y;
	int	r;

	r = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && ft_strlen(cmd[i]) > 1)
		{
			y = 1;
			while (cmd[i][y] == 'n')
				y++;
			if (y == (int)ft_strlen(cmd[i]))
				r = i;
		}
		else
			break ;
		i++;
	}
	if (r > 0)
		return (*t = r + 1, SUCCESS);
	return (*t = r + 1, FAIL);
}

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (checking_args(cmd, &i, 1) == SUCCESS)
	{
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i++], 1);
			if (cmd[i])
				printf(" ");
		}
		return (1);
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd("\n", 1);
	g_statesssss = 0;
	return (1);
}
