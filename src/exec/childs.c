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
		// if (data->file == -1 && data->type == READ)
		// 	exit(1);
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
	// close(data->pipefd[1]);
	// dup2(data->pipefd[0], STDIN_FILENO);
}

void	ft_exec_init(t_exec *data, t_env **env)
{
	// if (data->heredoc == 1)
	// 	data->command = ft_split(argv[3 + data->index_child], ' ');
	// else
	// 	data->command = ft_split(argv[2 + data->index_child], ' ');
	// if (data->command == NULL)
	// 	exit(1);
	int i;
	i = 0;
	if (data->type == WRITE)
	{
		while(data->file[i])
		{
			data->pipefd[1] = data->file[i];
			dup2(data->pipefd[1], STDOUT_FILENO);
			i++;
		}
	}
	i = 0;
	if (data->type == APPEND)
	{
		while(data->file[i])
		{
			data->pipefd[1] = data->file[i];
			dup2(data->pipefd[1], STDOUT_FILENO);
			i++;
		}
	}
	i = 0;
	if (data->type == READ || data->type == HEREDOC)
	{
		while(data->file[i])
		{
			data->pipefd[0] = data->file[i];
			dup2(data->pipefd[0], STDIN_FILENO);
			i++;
		}
	}

	if (ft_exec_builtins(data, env))
		exit (0);

	if (data->path_cmd == NULL)
	{
		// ft_free_all(new->cmd);
		// free(new->path_cmd);
		ft_message("Error: Command not found\n");
	}
}

int	ft_exec_builtins(t_exec *data, t_env **env)
{
	if (!ft_strncmp(data->cmd[0], "cd", 2))
	{
		// printf("aa%s", (*env)->str);
		ft_cd(env, data->cmd[1]);
		return (1);
	}
	// if (ft_strncmp(data->command[0], "echo", 4))
	if (!ft_strncmp(data->cmd[0], "env", 3))
	{
		ft_env(*env);
		return (1);
	}
	// if (ft_strncmp(data->command[0], "exit", 4))
	// if (ft_strncmp(data->command[0], "export", 6))
	if (!ft_strncmp(data->cmd[0], "pwd", 3))
	{
		ft_pwd();
		return (1);
	}
	// if (ft_strncmp(data->command[0], "unset", 5))
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

void	ft_error(char *error)
{
	perror(error);
	exit (1);
}

void	ft_message(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}
