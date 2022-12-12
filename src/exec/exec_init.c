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

void	ft_exec_init(t_exec *data, t_env **env)
{
	int			i;
	t_list_exec	p;
	struct stat	stats;

	i = 0;
	while (data->type[i])
	{
		ft_exec_init_2(data, i);
		i++;
	}
	if (ft_exec_builtins(data, env))
	{
		clear_env(env);
		while (data->prev)
			data = data->prev;
		p.first = data;
		exec_clear(&p);
		exit (g_statesssss);
	}
	ft_exec_init_3(data, env, 0, &stats);
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
	while (d->prev)
		d = d->prev;
	return (d);
}

void	ft_exec_init_3(t_exec *data, t_env **env, int y, struct stat *stats)
{
	t_list_exec	p;

	if (!data->path_cmd || (data->cmd && (ft_strcmp(data->cmd[0], "~")
				&& (!ft_strcmp(data->cmd[0], ".")
					|| !ft_strcmp(data->cmd[0], "..")
					|| !ft_strcmp(data->cmd[0], "")))))
	{
		if (data->cmd && !ft_strcmp(data->cmd[0], "."))
			y = 1;
		data = data_prev(data);
		p.first = data;
		exec_clear(&p);
		if (y)
			ft_message(".: usage: . filename\n", data, env, 2);
		ft_message("Error: Command not found\n", data, env, 127);
	}
	if ((stat(data->path_cmd, stats) == 0 && S_ISDIR(stats->st_mode))
		|| (data->cmd && !ft_strcmp(data->cmd[0], "~")))
	{
		data = data_prev(data);
		p.first = data;
		exec_clear(&p);
		ft_message(ERROR_1, data, env, 126);
	}
}

void	exec_init(t_list_exec *l)
{
	l->first = NULL;
	l->last = NULL;
}
