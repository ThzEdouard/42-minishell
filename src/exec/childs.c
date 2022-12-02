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
	if (!ft_check_builtins(data) && !data->path_cmd && !data->file)
		return ;
	if (pipe(data->pipefd) == -1)
		ft_error("Pipe Error");
	data->pid = fork();
	if (data->pid == -1)
		ft_error("Fork Error");
	if (data->pid == 0)
	{
		if (data->prev != NULL)
			dup2(data->prev->pipefd[0], STDIN_FILENO);
		if (data->next != NULL)
			dup2(data->pipefd[1], STDOUT_FILENO);
		ft_exec_init(data, env);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		execve(data->path_cmd, data->cmd, envp);
	}
	close(data->pipefd[1]);
	if (data->prev != NULL)
		close(data->prev->pipefd[0]);
}

int	ft_exec_builtins(t_exec *data, t_env **env)
{
	if (!ft_strncmp(data->cmd[0], "cd", 2))
		return (ft_cd(env, data->cmd[1]), 1);
	if (!ft_strncmp(data->cmd[0], "echo", 4))
		return (ft_echo(data->cmd), 1);
	if (!ft_strncmp(data->cmd[0], "env", 3))
		return (ft_env(*env), 1);
	if (!ft_strncmp(data->cmd[0], "exit", 4))
		return (ft_exit(data, env, data->cmd), 1);
	if (!ft_strncmp(data->cmd[0], "export", 6))
		return (ft_export(env, data->cmd), 1);
	if (!ft_strncmp(data->cmd[0], "pwd", 3))
		return (ft_pwd(), 1);
	if (!ft_strncmp(data->cmd[0], "unset", 5))
		return (ft_unset(env, data->cmd[1]), 1);
	return (0);
}

int	ft_check_builtins(t_exec *data)
{
	if (!ft_strncmp(data->cmd[0], "cd", 2))
		return (1);
	if (!ft_strncmp(data->cmd[0], "echo", 4))
		return (1);
	if (!ft_strncmp(data->cmd[0], "env", 3))
		return (1);
	if (!ft_strncmp(data->cmd[0], "exit", 4))
		return (1);
	if (!ft_strncmp(data->cmd[0], "export", 6))
		return (1);
	if (!ft_strncmp(data->cmd[0], "pwd", 3))
		return (1);
	if (!ft_strncmp(data->cmd[0], "unset", 5))
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
