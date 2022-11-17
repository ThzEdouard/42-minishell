/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:33:02 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/17 17:53:08 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handel(int sig)
{
	if (sig == SIGKILL)
	{
		printf("\n");
		g_statesssss = 1;
	}
	if (sig == SIGQUIT)
		g_statesssss = 1;
}