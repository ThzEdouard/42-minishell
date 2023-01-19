/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:17:12 by aradice           #+#    #+#             */
/*   Updated: 2022/10/13 16:46:35 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_childs(t_exec *data, char **envp, t_env **env)
{
	t_list_exec	p;

	if (pipe(data->pipefd) == -1)
		ft_error("Pipe Error");
	data->pid = fork();
	if (data->pid == -1)
		ft_error("Fork Error");
	if (data->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!data->cmd)
			ft_no_commands(data, envp, env, p);
		if (data->fileproblem)
			ft_exec_init(data, env, 1, envp);
		if (data->prev != NULL)
			dup2(data->prev->pipefd[0], STDIN_FILENO);
		if (data->next != NULL)
			dup2(data->pipefd[1], STDOUT_FILENO);
		ft_exec_init(data, env, 0, envp);
		ft_execve(data, envp);
	}
	close(data->pipefd[1]);
	if (data->prev != NULL && data->prev->cmd != NULL)
		close(data->prev->pipefd[0]);
}

void	ft_execve(t_exec *data, char **envp)
{
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	if (data->cmd)
		execve(data->path_cmd, data->cmd, envp);
}

void	ft_no_commands(t_exec *data, char **envp, t_env **env, t_list_exec p)
{
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	clear_env(env);
	while (data->prev)
		data = data->prev;
	ft_close_files(data);
	p.first = data;
	exec_clear(&p);
	if (envp)
		free(envp);
	exit(g_statesssss);
}

int	ft_check_redirs(t_exec *data)
{
	int	i;

	i = 0;
	while (data->type[i])
	{
		if (data->type[i] != WORD)
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}
