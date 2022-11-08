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

void	ft_open_files(t_exec *data, int i)
{
	t_exec *tmp;

	tmp = data;

	while (tmp)
	{
		i = 0;
		// if (!tmp->filename && tmp->next != NULL)
		// 	tmp->
		// tmp->file = ft_realoc_int(tmp->filename);
		if (!tmp->filename)
			return ;
		tmp->file = ft_realoc_int(tmp->filename);
		while(tmp->filename[i])
		{
			if (tmp->type == READ)
			{
				tmp->file[i] = open(tmp->filename[i], O_RDONLY);
				if (tmp->file[i] == -1)
					perror("Infile Error");
			}
			else if (tmp->type == WRITE)
			{
				tmp->file[i] = open(tmp->filename[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
				if (tmp->file[i] == -1)
					perror("Outfile Error");
			}
			else if (tmp->type == APPEND)
			{
				tmp->file[i] = open(tmp->filename[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (tmp->file[i] == -1)
					perror("Outfile Error");
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	ft_close_files(t_exec *data)
{
	t_exec *tmp;
	int i;
	i = 0;

	tmp = data;

	while (tmp)
	{
		i = 0;
		if (!tmp->filename)
			return ;
		while(tmp->filename[i])
		{
			if (tmp->type != HEREDOC)
				close(tmp->file[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	ft_check_heredoc(t_exec *data)
{
	t_exec *tmp;

	tmp = data;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_mode(t_exec *data)
{
	int i;

	i = 0;
	if (ft_check_heredoc(data))
	{
		ft_open_files(data, i);
		ft_here_doc(data, i);
		if (unlink("temp.tmp") == -1)
			ft_error("Temp File Error");
	}
	else
		ft_open_files(data, i);
}

void	ft_exec(t_exec *p, char **envp, t_env **env)
{
	t_exec	*tmp;
	t_exec	*tmp2;
	t_exec	*tmp3;
	int i = 0;


	tmp = p;
	tmp2 = p;
	tmp3 = p;
	ft_mode(tmp2);
	// dup2((&data)->infile, STDIN_FILENO);

	// ft_exec_init(tmp, envp);
	while (tmp3)
	{
		i++;
		tmp3 = tmp3->next;
	}
	tmp3 = p;
	if (i == 1 && ft_check_builtins(tmp3))
	{
		ft_exec_builtins(tmp3, env);
		return ;
	}

	while (tmp)
	{
		ft_childs(tmp, envp, env);
		tmp = tmp->next;
	}
	while (wait(&p->pid) > 0)
	{
		continue ;
	}
	ft_close_files(p);
}
