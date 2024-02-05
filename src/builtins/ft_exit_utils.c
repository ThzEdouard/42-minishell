/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:13:07 by aradice           #+#    #+#             */
/*   Updated: 2023/02/06 19:38:19 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_exit(t_exec *data, t_env **env, char **envp)
{
	ft_putstr_fd("exit\n", 0);
	ft_free_exit(data, env, g_statesssss, envp);
}

void	ft_closes(t_exec *tmp)
{
	ft_close_check(tmp->savein);
	ft_close_check(tmp->saveout);
	ft_close_check(tmp->pipefd[0]);
	ft_close_check(tmp->pipefd[1]);
}

void	ft_free_exit(t_exec *data, t_env **env, int code, char **envp)
{
	if (envp)
		free(envp);
	envp = NULL;
	clear_env(env);
	exec_clears(data);
	exit(code);
}
