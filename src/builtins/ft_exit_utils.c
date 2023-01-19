/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:13:07 by aradice           #+#    #+#             */
/*   Updated: 2023/01/19 18:13:35 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_exit(t_exec *data, t_env **env)
{
	ft_putstr_fd("exit\n", 0);
	ft_free_exit(data, env, g_statesssss);
}

void	ft_closes(t_exec *tmp)
{
	close(tmp->savein);
	close(tmp->saveout);
	close(tmp->pipefd[0]);
	close(tmp->pipefd[1]);
}

void	ft_free_exit(t_exec *data, t_env **env, int code)
{
	clear_env(env);
	exec_clears(data);
	exit(code);
}
