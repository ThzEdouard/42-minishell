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

int	ft_open_files_2(t_exec *tmp, int i)
{
	if (tmp->type[i] == READ)
	{
		tmp->file[i] = open(tmp->filename[i], O_RDONLY);
		if (tmp->file[i] == -1)
		{
			perror("Infile Error");
			return (FAIL);
		}
	}
	else if (tmp->type[i] == WRITE)
	{
		tmp->file[i] = open(tmp->filename[i], O_RDWR
				| O_CREAT | O_TRUNC, 0644);
		if (tmp->file[i] == -1)
			perror("Outfile Error");
		// puts(tmp->filename[i]);
	}
	else if (tmp->type[i] == APPEND)
	{
		tmp->file[i] = open(tmp->filename[i], O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (tmp->file[i] == -1)
			perror("Outfile Error");		
	}
	// puts(tmp->filename[i]);
	return (SUCCESS);
}

int	ft_open_files(t_exec *data, int i)
{
	t_exec	*tmp;

	tmp = data;
	while (tmp)
	{
		i = 0;
		while (!tmp->filename && tmp->next)
			tmp = tmp->next;
		if (!tmp->filename)
			return (SUCCESS);
		tmp->file = ft_realoc_int(tmp->filename);
		while (tmp->filename[i])
		{
			// puts(tmp->filename[i]);
			// printf("sss%d\n%d::\n", tmp->type[i], i);
			if (ft_open_files_2(tmp, i) == FAIL)
				return (FAIL);
			i++;
		}
		tmp = tmp->next;
	}
	// printf("i = %d\n", i);
	return (SUCCESS);
}

void	ft_close_files(t_exec *data)
{
	t_exec	*tmp;
	int		i;

	i = 0;
	tmp = data;
	while (tmp)
	{
		i = 0;
		while (!tmp->filename && tmp->next)
			tmp = tmp->next;
		if (!tmp->filename)
			return ;
		while (tmp->filename[i])
		{
			if (tmp->type[i] != HEREDOC)
				close(tmp->file[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	ft_mode(t_exec *data)
{
	int	i;

	i = 0;
	if (ft_check_heredoc(data))
	{
		if (ft_open_files(data, i) == FAIL)
			return (FAIL);
		while(data->filename[i])
		{
			if(data->type[i] == HEREDOC)
				ft_here_doc(data, i);
			i++;
			// printf("type: %d\n i: %d\n file: %d\n filename: %s\n", data->type[i], i, data->file[i], data->filename[i]);
			if(data->type[i] == HEREDOC)
			{
				if (unlink("temp.tmp") == -1)
					ft_error("Temp File Error");
			}
		}
		// if (unlink("temp.tmp") == -1)
		// 	ft_error("Temp File Error");
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
		// printf("TYPE= %d", tmp->type[0]);
		i++;
		tmp = tmp->next;
	}
	tmp = p;
	if (i == 1 && tmp->cmd && ft_check_builtins(tmp) && !ft_check_redirs(tmp))//
	{
		ft_exec_builtins_init(tmp, env);
		ft_close_files(p);
		dup2(tmp->savein, STDIN_FILENO);
		dup2(tmp->saveout, STDOUT_FILENO);
		close(tmp->savein);
		close(tmp->saveout);
		return ;
	}
	if (i == 1 && tmp->cmd && ft_check_builtins(tmp))
	{
			ft_exec_builtins(tmp, env);
			return ;
	}
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
