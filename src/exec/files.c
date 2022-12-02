/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 01:28:13 by aradice           #+#    #+#             */
/*   Updated: 2022/12/02 01:29:46 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			if (ft_open_files_2(tmp, i) == FAIL)
				return (FAIL);
			i++;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

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
	}
	else if (tmp->type[i] == APPEND)
	{
		tmp->file[i] = open(tmp->filename[i], O_WRONLY
				| O_CREAT | O_APPEND, 0644);
		if (tmp->file[i] == -1)
			perror("Outfile Error");
	}
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