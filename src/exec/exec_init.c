/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:23:42 by aradice           #+#    #+#             */
/*   Updated: 2022/12/03 20:20:06 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_init(t_exec *data, t_env **env, int x, char **envp)
{
	int			i;
	t_list_exec	p;

	i = 0;
	while (data->type[i])
	{
		ft_exec_init_2(data, i);
		i++;
	}
	if (ft_check_builtins(data) || x)
	{
		ft_close_free(data, envp);
		if (data->prev != NULL && data->prev->cmd != NULL)
			ft_close_check(data->prev->pipefd[0]);
		ft_exec_builtins(data, env, NULL);
		clear_env(env);
		while (data->prev)
			data = data->prev;
		ft_close_files(data);
		p.first = data;
		exec_clear(&p);
		exit (g_statesssss);
	}
}

void	ft_exec_init_2(t_exec *data, int i)
{
	int	y;

	y = 0;
	if (data->type[i] == APPEND || data->type[i] == WRITE)
	{
		while (data->file[y] && data->file[y] != -1)
		{
			data->pipefd[1] = data->file[y];
			dup2(data->pipefd[1], STDOUT_FILENO);
			y++;
		}
	}
	if (data->type[i] == READ || data->type[i] == HEREDOC)
	{
		while (data->file[y] && data->file[y] != -1)
		{
			data->pipefd[0] = data->file[y];
			dup2(data->pipefd[0], STDIN_FILENO);
			y++;
		}
	}
}

t_exec	*data_prev(t_exec *data)
{
	t_exec	*d;

	d = data;
	if (data->prev != NULL && data->prev->cmd != NULL)
		ft_close_check(data->prev->pipefd[0]);
	ft_close_check(data->pipefd[0]);
	ft_close_check(data->pipefd[1]);
	while (d->prev)
		d = d->prev;
	return (d);
}

int	error_mgs_fork(t_exec *data)
{
	int	fd;
	DIR	*folder;

	if (!data->path_cmd)
		return (ft_putendl_fd("Command not found", 2), 127);
	fd = open(data->path_cmd, O_WRONLY);
	folder = opendir(data->path_cmd);
	if (ft_strchr(data->path_cmd, '/') == NULL)
		return (ft_putendl_fd("Command not found", 2), 127);
	if (fd == -1 && folder != NULL)
		return (ft_putendl_fd("Is a directory", 2), 126);
	return (ft_putendl_fd("Command not found", 2), 127);
}
