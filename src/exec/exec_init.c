/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:23:42 by aradice           #+#    #+#             */
/*   Updated: 2022/12/02 11:39:01 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exec_init(t_exec *data, t_env **env)
{
	int	i;

	i = 0;
	while (data->type[i])
	{
		ft_exec_init_2(data, i);
		i++;
	}
	if (ft_exec_builtins(data, env))
		exit (0);
	if (data->path_cmd == NULL)
		ft_message("Error: Command not found\n");
}

void	ft_exec_init_2(t_exec *data, int i)
{
	if (data->type[i] == APPEND || data->type[i] == WRITE)
	{
		while (*data->file != 0)
		{
			data->pipefd[1] = *data->file;
			dup2(data->pipefd[1], STDOUT_FILENO);
			data->file++;
		}
	}
	if (data->type[i] == READ || data->type[i] == HEREDOC)
	{
		while (*data->file != 0)
		{
			data->pipefd[0] = *data->file;
			dup2(data->pipefd[0], STDIN_FILENO);
			data->file++;
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
	if (data->type[i] == APPEND || data->type[i] == WRITE)
	{
		while (*data->file != 0)
		{
			data->pipefd[1] = *data->file;
			dup2(data->pipefd[1], STDOUT_FILENO);
			data->file++;
		}
	}
	if (data->type[i] == READ || data->type[i] == HEREDOC)
	{
		while (*data->file != 0)
		{
			data->pipefd[0] = *data->file;
			dup2(data->pipefd[0], STDIN_FILENO);
			data->file++;
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
