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

void	sig_int_here(int sig, siginfo_t *info, void *tmp)
{
	(void)sig;
	(void)info;
	(void)tmp;
	ft_putstr_fd("\b\b\n", 0);
	close(0);
	g_statesssss = 1300;
}

void	sig_here_init(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_int_here;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_int(int sig, siginfo_t *info, void *tmp)
{
	(void)sig;
	(void)tmp;
	if (info->si_pid != 0)
	{
		ft_putstr_fd("\n", 1);
		g_statesssss = 130;
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}
