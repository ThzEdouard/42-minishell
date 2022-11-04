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

void	ft_here_doc(t_exec *data)
{
	char	*line;
	int		temp;

	temp = open("temp.tmp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (temp == -1)
		ft_error("File Error");
	line = readline(STDIN_FILENO);
	while (1)
	{
		printf("q%sq   q%sq", line, data->filename[0]);
		if (!ft_strncmp(line, data->filename[0], ft_strlen(data->filename[0])))
		{
			if (ft_strlen(data->filename[0]) == ft_strlen(line))
			{
				close(temp);
				free(line);
				data->file[0] = open("temp.tmp", O_RDONLY);
				if (data->file[0] == -1)
					ft_error("File Error");
				break ;
			}
		}
		write(temp, line, ft_strlen(line));
		free(line);
		line = readline(STDIN_FILENO);
	}
}
