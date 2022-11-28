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
	if (info->si_pid == 0)
	{
		printf("\b\b \n🤬");
		g_statesssss = 1;
	}
	else
	{
		printf("\n");
		g_statesssss = 130;
		prompt(NULL,NULL);
		printf("doudou > ");
	}
}

void	sig_quit(int sig, siginfo_t *info, void *tmp)
{
	(void)tmp;
	(void)sig;
	if (info->si_pid == 0)
	{
		printf("Quit (core dumped)\n");
		g_statesssss = 131;
	}
	else
		printf("\b\b  \b\b");
}