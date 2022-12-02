/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:36:47 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/11 11:16:50 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(void)
{
	char	run[256];

	if (getcwd(run, sizeof(run)) == NULL)
	{
		perror("error getcwd()");
		g_statesssss = 1;
		return (1);
	}
	else
		printf("%s\n", run);
	g_statesssss = 0;
	return (0);
}
