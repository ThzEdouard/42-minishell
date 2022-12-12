/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:33:11 by aradice           #+#    #+#             */
/*   Updated: 2022/12/12 16:12:51 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		}
	}
	if (data->type[i] == READ || data->type[i] == HEREDOC)
	{
		while (data->file[y] != 0)
		{
			data->pipefd[0] = data->file[y];
			dup2(data->pipefd[0], STDIN_FILENO);
			y++;
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
