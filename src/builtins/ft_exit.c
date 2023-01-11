/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 05:36:45 by aradice           #+#    #+#             */
/*   Updated: 2022/11/10 05:36:45 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_clears(t_exec *l)
{
	t_exec	*tmp;
	t_exec	*elem;

	elem = l;
	while (elem)
	{
		tmp = elem;
		if (tmp->cmd && tmp->cmd[0] == tmp->path_cmd)
			ft_free_all(tmp->cmd);
		else
		{
			ft_free_all(tmp->cmd);
			if (tmp->path_cmd)
				free(tmp->path_cmd);
		}
		tmp->path_cmd = NULL;
		close(tmp->savein);
		close(tmp->saveout);
		ft_free_all(tmp->filename);
		if (elem->type)
			free(elem->type);
		elem = elem->next;
		free(tmp);
	}
}

void	ft_free_exit(t_exec *data, t_env **env, int code)
{
	printf("exit\n");
	clear_env(env);
	exec_clears(data);
	exit(code);
}

void	ft_exit_util(t_exec *data, t_env **env, char **cmd)
{
	int	y;

	y = 0;
	while (cmd[1][y])
	{
		if (cmd[1][y] < '0' || cmd[1][y] > '9')
		{
			if (y == 0 && cmd[1][y] == '-')
			{
				y++;
				continue ;
			}
			else
			{
				printf("bash: exit: %s: numeric argument required\n", cmd[1]);
				ft_free_exit(data, env, 2);
			}
		}
		y++;
	}
}

void	ft_exit(t_exec *data, t_env **env, char **cmd)
{
	int	i;

	i = 0;
	printf("eeee");
	while (cmd[i])
		i++;
	if (i == 1)
		ft_free_exit(data, env, g_statesssss);
	ft_exit_util(data, env, cmd);
	if (i > 2)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	else if (i == 2)
		g_statesssss = ft_atoi(cmd[1]);
	if (g_statesssss < 0)
		g_statesssss = 256 - (-g_statesssss % 256);
	else
		g_statesssss = g_statesssss % 256;
	ft_free_exit(data, env, g_statesssss);
}
