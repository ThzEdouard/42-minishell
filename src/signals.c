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


void	sig_int(int sig, siginfo_t *info, void *tmp)
{
	(void)sig;
	(void)tmp;
	if (info->si_pid != 0)
	{
		ft_putstr_fd("\n", 1);
		g_statesssss = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putstr_fd("\b\b\n", 1);
}
