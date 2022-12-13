/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:14:41 by aradice           #+#    #+#             */
/*   Updated: 2022/12/13 17:12:08 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	test(char *line, char start)
{
	int	i;

	i = 2;
	line++;
	while (*line && *line != start)
	{
		line++;
		// if (*line == start && *line + 1 && *line + 1 != 32)
		// 	line++;
		i++;
	}
	if (*line == start)
		line++;
	return (i);
}

void	test_parse(char **lines, int *en, t_trace *t)
{
	char	*line;
	int		end;

	end = *en;
	line = *lines;
	while (*line && *line != 32 && !ft_space(*line))
	{
		end++;
		line++;
		// if (*line && (*line == 34 || *line == 39) && *line + 1
		// 	&& (*line + 1 != 34 || *line + 1 != 39))
		// {
		// 	end++;
		// 	line++;
		// 	printf("test\n");
		// }
		*t = YES;
	}
	*lines = line;
	*en = end;
}
