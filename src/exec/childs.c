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
	if (pipe(data->pipefd) == -1)
		ft_error("Pipe Error");
	data->pid = fork();
	if (data->pid == -1)
		ft_error("Fork Error");
	if (data->pid == 0)
	{
		if (data->prev != NULL && data->prev->cmd != NULL)
			dup2(data->prev->pipefd[0], STDIN_FILENO);
		if (data->next != NULL)
			dup2(data->pipefd[1], STDOUT_FILENO);
		ft_exec_init(data, env);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		if (data->cmd)
			execve(data->path_cmd, data->cmd, envp);
	}
	close(data->pipefd[1]);
	if (data->prev != NULL && data->prev->cmd != NULL)
		close(data->prev->pipefd[0]);
}

int	ft_exec_builtins(t_exec *data, t_env **env)
{
	if (data->cmd && !ft_strcmp(data->cmd[0], "cd"))
		return (ft_cd(env, data->cmd[1]), 1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "echo"))
		return (ft_echo(data->cmd), 1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "env"))
		return (ft_env(*env), 1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "exit"))
		return (ft_exit(data, env, data->cmd), 1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "export"))
		return (ft_export(env, data->cmd), 1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "pwd"))
		return (ft_pwd(), 1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "unset"))
		return (ft_unset(env, data->cmd[1]), 1);
	return (0);
}

int	ft_check_builtins(t_exec *data)
{
	if (data->cmd && !ft_strcmp(data->cmd[0], "cd"))
		return (1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "echo"))
		return (1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "env"))
		return (1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "exit"))
		return (1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "export"))
		return (1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "pwd"))
		return (1);
	if (data->cmd && !ft_strcmp(data->cmd[0], "unset"))
		return (1);
	return (0);
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
