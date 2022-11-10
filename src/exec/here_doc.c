/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 01:29:02 by aradice           #+#    #+#             */
/*   Updated: 2022/10/13 16:45:49 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_here_doc(t_exec *data, int i)
{
	char	*line;
	int		temp;

	data->file = malloc(10000);
	temp = open("temp.tmp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (temp == -1)
		ft_error("File Error");
	line = readline(STDIN_FILENO);
	while (1)
	{
		if (!ft_strncmp(line, data->filename[i], ft_strlen(data->filename[i])))
		{
			if (ft_strlen(data->filename[i]) == ft_strlen(line))
			{
				close(temp);
				free(line);
				data->file[i] = open("temp.tmp", O_RDONLY);
				if (data->file[i] == -1)
					ft_error("File Error");
				break ;
			}
		}
		write(temp, line, ft_strlen(line));
		free(line);
		line = readline(STDIN_FILENO);
	}
}