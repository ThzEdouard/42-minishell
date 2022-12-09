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
	int		i;
	int		test;
	int		*filenumber;
	t_exec	*tmp;

	tmp = data;
	test = 0;
	filenumber = &test;
	i = 0;
	if (ft_check_heredoc(data))
	{
		if (ft_open_files(data, i, filenumber) == FAIL)
			return (FAIL);
		ft_mode_heredoc(tmp, i, filenumber);
	}
	else
		if (ft_open_files(data, i, filenumber) == FAIL)
			return (FAIL);
	return (SUCCESS);
}

void	ft_mode_heredoc(t_exec *tmp, int i, int *filenumber)
{
	int		*iv2;

	iv2 = &i;
	while (tmp)
	{
		*iv2 = 0;
		while (tmp->filename[*iv2])
		{
			if (tmp->type[*iv2] == HEREDOC)
			{
				ft_here_doc(tmp, *iv2, filenumber);
				*filenumber = *filenumber + 1;
			}
			*iv2 = *iv2 + 1;
		}
		tmp = tmp->next;
	}
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
		if (tmp->cmd)
			ft_childs(tmp, envp, env);
		tmp = tmp->next;
	}
	while (wait(&p->pid) > 0)
	{
		g_statesssss = p->pid / 256;
		continue ;
	}
	tmp = p;
	ft_unlink_heredoc(tmp);
	ft_close_files(p);
}

void	ft_unlink_heredoc(t_exec *tmp)
{
	int	i;

	i = 0;
	if (ft_check_heredoc(tmp))
	{
		while (tmp)
		{
			i = 0;
			while (tmp->type[i] == HEREDOC)
			{
				if (unlink(tmp->filename[i]) == -1)
					ft_error("Temp File Error");
				i++;
			}
			tmp = tmp->next;
		}
	}
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
