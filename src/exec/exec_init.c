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
	int	i;
	struct stat stats;
	i = 0;
	t_list_exec p;
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
		printf("ici je pass ?\n");
		exit (0);
	}

	if (data->path_cmd == NULL && (data->cmd &&  ft_strcmp(data->cmd[0], "~")))
	{
		while (data->prev)
			data = data->prev;
		ft_message("Error: Command not found\n", data, env,127);
	}

	if ((stat(data->path_cmd, &stats) == 0 && S_ISDIR(stats.st_mode)) || (data->cmd &&  !ft_strcmp(data->cmd[0], "~")))
	{
		while (data->prev)
			data = data->prev;
		ft_message(ERROR_1, data, env, 126);
	}
}

void	ft_exec_init_2(t_exec *data, int i)
{
	int	y;

	y = 0;
	if (data->type[i] == APPEND || data->type[i] == WRITE)
	{
		while (data->file[y])
		{
			data->pipefd[1] = data->file[y];
			dup2(data->pipefd[1], STDOUT_FILENO);
			y++;
			// data->file++;
		}
	}
	if (data->type[i] == READ || data->type[i] == HEREDOC)
	{
		while (data->file[y])
		{
			data->pipefd[0] = data->file[y];
			dup2(data->pipefd[0], STDIN_FILENO);
			y++;
			// data->file++;
		}
	}
}

void	ft_exec_builtins_init(t_exec *data, t_env **env)
{
	int	i;

	i = 0;
	while (data->type[i])
	{
		ft_exec_builtins_init_2(data, i);
		i++;
	}
	if (ft_exec_builtins(data, env))
		return ;
}

void	ft_exec_builtins_init_2(t_exec *data, int i)
{
	int	y;

	y = 0;
	if (data->type[i] == APPEND || data->type[i] == WRITE)
	{
		while (data->file[y] != 0)
		{
			data->pipefd[1] = data->file[y];
			dup2(data->pipefd[1], STDOUT_FILENO);
			y++;
			// data->file++;
		}
	}
	if (data->type[i] == READ || data->type[i] == HEREDOC)
	{
		while (data->file[y] != 0)
		{
			data->pipefd[0] = data->file[y];
			dup2(data->pipefd[0], STDIN_FILENO);
			y++;
			// data->file++;
		}
	}
}

void	add_exec_init(t_list_exec *l, t_add *values)
{
	l->first = NULL;
	l->last = NULL;
	values->i = 0;
	values->y = 0;
	values->j = 0;
	values->filename = NULL;
	values->command = NULL;
	values->type = NULL;
}
