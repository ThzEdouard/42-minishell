/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:19:53 by aradice           #+#    #+#             */
/*   Updated: 2023/02/06 20:19:41 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_little_closes(t_exec *tmp)
{
	ft_close_check(tmp->pipefd[0]);
	ft_close_check(tmp->pipefd[1]);
}

void	ft_exec_process_builtins(t_exec *tmp,
		t_exec *p, t_env **env, char **envp)
{
	ft_exec_builtins_init(tmp, env, envp);
	ft_close_files(p);
	dup2(tmp->savein, STDIN_FILENO);
	dup2(tmp->saveout, STDOUT_FILENO);
	ft_close_check(tmp->savein);
	ft_close_check(tmp->saveout);
}

void	exec_init(t_list_exec *l)
{
	l->first = NULL;
	l->last = NULL;
}

void	ft_close_free(t_exec *data, char **envp)
{
	if (envp)
		free(envp);
	envp = NULL;
	ft_close_check(data->pipefd[0]);
	ft_close_check(data->pipefd[1]);
}

void	ft_close_check(int tmp)
{
	if (tmp != -1)
		close (tmp);
}
