/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:36:59 by aradice           #+#    #+#             */
/*   Updated: 2022/12/11 14:49:46 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verification_quote_2(int *start, char *line)
{
	if (!ft_strlen(line))
		return (g_statesssss = 0, FAIL);
	if (*line == '!')
		return (g_statesssss = 1, FAIL);
	if (*start == 0 && (*line == 59 || *line == 40
			|| *line == 41 || *line == 92))
	{
		if (start == 0 && (*(line + 1) == 59 || *(line + 1) == 40
				|| *(line + 1) == 41))
			return (ft_quit_error(*line, 2), FAIL);
		return (ft_quit_error(*line, 1), FAIL);
	}
	return (SUCCESS);
}

int	verif_up(char **lines)
{
	char	*line;

	line = *lines;
	if (ft_strlen(line) == 1 && (*line == ':' || *line == '!'))
		return (FAIL);
	while (*line == '#' || *line == '\f' || *line == '\n'
		|| *line == '\r' || *line == '\t' || *line == '\v' || *line == ' ')
		line++;
	if (!ft_strlen(line))
		return (g_statesssss = 0, FAIL);
	*lines = line;
	return (SUCCESS);
}

int	up_code(char *line)
{
	if (!ft_strlen(line))
		return (g_statesssss = 0, FAIL);
	if (*line == '!')
		return (g_statesssss = 1, FAIL);
	if (*line == ':')
		return (g_statesssss = 0, FAIL);
	return (SUCCESS);
}

int	verification_quote(char *line)
{
	int		start;
	char	c;

	start = 0;
	c = 0;
	if (verif_up(&line) || up_code(line))
		return (FAIL);
	while (*line)
	{
		if (start == 0 && (*line == 34 || *line == 39))
		{
			c = *line;
			start++;
			line++;
		}
		if (*line && verification_quote_2(&start, line) == FAIL)
			return (FAIL);
		if (*line && start == 1 && *line == c)
			start = 0;
		if (*line)
			line++;
	}
	if (start == 1)
		return (ft_quit_error(c, 1), FAIL);
	return (SUCCESS);
}

int	ft_space(char c)
{
	if (c != 34 && c != 39 && c != 60 && c != 62 && c != 124)
		return (0);
	return (1);
}
