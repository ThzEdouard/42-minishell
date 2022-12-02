/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:16:29 by aradice           #+#    #+#             */
/*   Updated: 2022/10/13 16:41:52 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_mode(t_exec *data)
{
	int	i;

	i = 0;
	if (ft_check_heredoc(data))
	{
		if (ft_open_files(data, i) == FAIL)
			return (FAIL);
		while (data->filename[i])
		{
			if (data->type[i] == HEREDOC)
				ft_here_doc(data, i);
			i++;
			if (data->type[i] == HEREDOC)
			{
				if (unlink("temp.tmp") == -1)
					ft_error("Temp File Error");
			}
		}
	}
	else
		if (ft_open_files(data, i) == FAIL)
			return (FAIL);
	return (SUCCESS);
}

void	ft_exec(t_exec *p, char **envp, t_env **env)
{
	t_exec	*tmp;
	int		i;

	i = 0;
	tmp = p;
	if (ft_mode(tmp) == FAIL)
		return ;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tmp = p;
	if (i == 1 && tmp->cmd && ft_check_builtins(tmp) && !ft_check_redirs(tmp))
	{
		ft_exec_process_builtins(tmp, p, env);
		return ;
	}
	if (i == 1 && tmp->cmd && ft_check_builtins(tmp))
	{
		ft_exec_builtins(tmp, env);
		return ;
	}
	ft_exec_process(tmp, p, envp, env);
}

void	ft_exec_process(t_exec *tmp, t_exec *p, char **envp, t_env **env)
{
	while (tmp)
	{
		ft_childs(tmp, envp, env);
		tmp = tmp->next;
	}
	while (wait(&p->pid) > 0)
		continue ;
	tmp = p;
	if (ft_check_heredoc(tmp))
	{
		if (unlink("temp.tmp") == -1)
			ft_error("Temp File Error");
	}
	ft_close_files(p);
}

void	ft_exec_process_builtins(t_exec *tmp, t_exec *p, t_env **env)
{
	ft_exec_builtins_init(tmp, env);
	ft_close_files(p);
	dup2(tmp->savein, STDIN_FILENO);
	dup2(tmp->saveout, STDOUT_FILENO);
	close(tmp->savein);
	close(tmp->saveout);
}
