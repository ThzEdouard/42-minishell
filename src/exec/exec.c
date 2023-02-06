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
		while (tmp->filename && tmp->filename[*iv2])
		{
			if (tmp->type && tmp->type[*iv2] == HEREDOC)
			{
				ft_heredoc(tmp, *iv2, filenumber);
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
	if (i == 1 && tmp->cmd && ft_check_builtins(tmp)
		&& !ft_check_redirs(tmp) && g_statesssss != 1300)
	{
		ft_exec_process_builtins(tmp, p, env, envp);
		return ;
	}
	if (i == 1 && tmp->cmd && ft_check_builtins(tmp) && g_statesssss != 1300)
	{
		ft_exec_builtins(tmp, env, envp);
		return ;
	}
	ft_exec_process(tmp, p, envp, env);
}

void	ft_exec_process(t_exec *tmp, t_exec *p, char **envp, t_env **env)
{
	while (tmp && g_statesssss != 1300)
	{
		ft_childs(tmp, envp, env);
		tmp = tmp->next;
	}
	tmp = p;
	while (tmp && waitpid(tmp->pid, &g_statesssss, 0)
		> 0 && g_statesssss != 1300)
	{
		if (WTERMSIG(g_statesssss) == 2)
		{
			ft_putstr_fd("\n", 0);
			g_statesssss = 130;
		}
		else if (WTERMSIG(g_statesssss) == 3)
		{
			ft_putstr_fd("\n", 0);
			g_statesssss = 130;
		}
		else
			g_statesssss = WEXITSTATUS(g_statesssss);
		ft_little_closes(tmp);
		tmp = tmp->next;
	}
	ft_exec_process_2(tmp, p);
}

void	ft_exec_process_2(t_exec *tmp, t_exec *p)
{
	tmp = p;
	ft_close_check(tmp->pipefd[0]);
	ft_close_check(tmp->pipefd[1]);
	ft_unlink_heredoc(tmp);
	ft_close_files(p);
	if (g_statesssss == 1300)
	{
		dup2(tmp->savein, 0);
		ft_close_check(tmp->savein);
		g_statesssss = 130;
	}
}
