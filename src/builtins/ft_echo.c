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

// static int checking_args(char **cmd)
// {
// 	return (SUCCESS);
// }

void	ft_echo(char **cmd)
{
	int i;

	i = 1;
	while(cmd[i])
	{
		printf("%s ",cmd[i]);
		i++;
	}
	printf("\n");
}