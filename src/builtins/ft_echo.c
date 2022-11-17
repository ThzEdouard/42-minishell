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

static int	checking_args(char **cmd, int *t, int i)
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
			printf ("y = %d len = %d\n", y, ft_strlen(cmd[i]));
			if (y == ft_strlen(cmd[i]))
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

static void	check_quite(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == 34 || cmd[i][0] == 36)
		{
			cmd[i] = ft_free_substr(cmd[i], 1, ft_strlen(cmd[i]) - 2);
		}
		i++;
	}
}

int	ft_echo(char **cmd)
{
	int	i;

	i = 1;
	check_quite(cmd);
	if (checking_args(cmd, &i, 1) == SUCCESS)
	{
		while (cmd[i])
		{
			printf("%s", cmd[i++]);
			if (cmd[i])
				printf(" ");
		}
		return (1);
	}
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
	printf("\n");
	g_statesssss = 0;
	return (1);
}
