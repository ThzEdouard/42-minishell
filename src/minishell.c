/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:23 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/06 19:41:55 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_statesssss;

void	init_sig(void)
{
	struct sigaction	sa;
	struct sigaction	se;

	sa.sa_sigaction = sig_int;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	se.sa_sigaction = sig_quit;
	se.sa_flags = SA_SIGINFO;
	sigemptyset(&se.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &se, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	g_statesssss = 0;
	(void) argc;
	(void) argv;
	if (envp && envp[0])
		generator_env(&env, envp);
	else
		env = NULL;
	prompter(&env, envp);
	if (env)
		clear_env(&env);
	return (SUCCESS);
}
