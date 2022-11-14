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
//a finir
// static int checking_code(char **cmd)
// {
//
// }

static int	checking_args(char **cmd, int *t)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	x = 0;
	while (cmd[i] && x == 0)
	{
		if (!strcmp(cmd[i], "echo"))
			i++;
		y = 0;
		while (cmd[i][y])
		{
			if (y == 0 && cmd[i][0] != '-')
			{
				x = 0;
				break ;
			}
			if (y != 0 && cmd[i][y] != 'n')
			{
				x = 0;
				break ;
			}
			x++;
			y++;
		}
		i++;
	}
	if (x > 0)
		return (*t = i, SUCCESS);
	return (FAIL);
}

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	if (checking_args(cmd, &i) == SUCCESS)
	{
		while (cmd[i])
		{
			printf("%s", cmd[i]);
		}
		return (1);
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
	}
	printf("\n");
	return (1);
}
