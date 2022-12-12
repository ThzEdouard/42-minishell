/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 23:28:12 by aradice           #+#    #+#             */
/*   Updated: 2022/05/24 23:28:12 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_new_staticstr(char *staticstr)
{
	int		i;
	int		y;
	char	*newstr;

	i = 0;
	y = 0;
	while (staticstr[i] && staticstr[i] != '\n')
		i++;
	if (!staticstr[i])
	{
		free(staticstr);
		return (NULL);
	}
	newstr = malloc(sizeof(char) * (ft_strlen_gnl(staticstr) - i + 1));
	if (!newstr)
		return (NULL);
	i++;
	while (staticstr[i])
		newstr[y++] = staticstr[i++];
	newstr[y] = '\0';
	free(staticstr);
	return (newstr);
}

char	*ft_get_line(char *staticstr)
{
	int		i;
	char	*line;

	i = 0;
	if (!staticstr[i])
		return (NULL);
	while (staticstr[i] && staticstr[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (staticstr[i] && staticstr[i] != '\n')
	{
		line[i] = staticstr[i];
		i++;
	}
	if (staticstr[i] == '\n')
	{
		line[i] = staticstr[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *staticstr)
{
	int		readval;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readval = 1;
	while (!ft_strchr_gnl(staticstr, '\n') && readval != 0)
	{
		readval = read(fd, buffer, BUFFER_SIZE);
		if (readval == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[readval] = '\0';
		if (!ft_strlen_gnl(buffer))
			return (free(buffer) , NULL);
		staticstr = ft_strjoin_gnl(staticstr, buffer);
	}
	free(buffer);
	return (staticstr);
}

char	*get_next_line(int fd)
{
	char	*staticstr;

	staticstr = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	staticstr = ft_read(fd, staticstr);
	if (!staticstr)
		return (NULL);
	return (staticstr);
}
