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

void	ft_here_doc(t_exec *data, int i, int *filenumber)
{
	char	*line;
	char	*tmpfilename;
	// int		temp;

	// temp = open("temp.tmp", O_WRONLY | O_APPEND | O_CREAT, 0644);
	// if (temp == -1)
		// ft_error("File Error");
	write(STDIN_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (1)
	{
		printf("line: %s - filenam[i]: %s - len: %d - fnum: %d - i: %d\n", line, data->filename[i], ft_strlen(data->filename[i]), *filenumber, i);
		if (!line || !ft_strncmp(line, data->filename[i], ft_strlen(data->filename[i])))
		{
			if (!line || ft_strlen(data->filename[i]) == (ft_strlen(line) - 1))
			{
				tmpfilename = ft_strjoin("tmp", ft_itoa(*filenumber));
				printf("filename: %s\n", tmpfilename);
				close(data->file[i]);
				if (line)
					free(line);
				data->file[i] = open(tmpfilename, O_RDONLY);
				if (data->file[i] == -1)
					ft_error("File Error");
				break ;
			}
		}
		ft_here_doc_2(line, data->file[i]);
		line = get_next_line(STDIN_FILENO);
	}
	free(data->filename[i]);
	// data->filename[i] = tmpfilename;
}

void	ft_here_doc_2(char *line, int temp)
{
	write(temp, line, ft_strlen(line));
	free(line);
	write(STDIN_FILENO, "> ", 2);
}

int	ft_check_heredoc(t_exec *data)
{
	t_exec	*tmp;
	int		i;

	i = 0;
	tmp = data;
	while (tmp && tmp->type)
	{
		while (tmp->type[i])
		{
			if (tmp->type[i] == HEREDOC)
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
