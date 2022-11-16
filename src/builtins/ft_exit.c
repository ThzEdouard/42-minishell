/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 05:36:45 by aradice           #+#    #+#             */
/*   Updated: 2022/11/10 05:36:45 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(char **cmd)
{
	int val;
	int i;
	int y;

	val = 0;
	i = 0;
	y = 0;
	while(cmd[i])
		i++;
	if (i == 1)
		exit(0);
	while(cmd[1][y])
		{
			if (cmd[1][y] < '0' || cmd[1][y] > '9')
			{
				if(y == 0 && cmd[1][y] == '-')
				{
					y++;
					continue ;
				}
				else
				{
					printf("bash: exit: %s: numeric argument required\n", cmd[1]);
					exit(2);
				}
			}
			y++;
		}
	if (i > 2)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	else if (i == 2)
		val = ft_atoi(cmd[1]);

	if (val < 0)
		val = 256 - (-val % 256);
	else
		val = val % 256;
	// printf("VAL= %d",val);
	exit(val);
}
