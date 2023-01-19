/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:19:53 by aradice           #+#    #+#             */
/*   Updated: 2023/01/19 18:50:06 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_little_closes(t_exec *tmp)
{
	close(tmp->pipefd[0]);
	close(tmp->pipefd[1]);
}

void	ft_exec_process_builtins(t_exec *tmp, t_exec *p, t_env **env)
{
	ft_exec_builtins_init(tmp, env);
	ft_close_files(p);
	dup2(tmp->savein, STDIN_FILENO);
	dup2(tmp->saveout, STDOUT_FILENO);
	close(tmp->savein);
	close(tmp->saveout);
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
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}
