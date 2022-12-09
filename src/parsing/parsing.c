/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:28 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/08 14:32:06 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_space(char c)
{
	if (c != 34 && c != 39 && c != 60 && c != 62 && c != 124)
		return (0);
	return (1);
}

int	test(char *line, char start)
{
	int	i;

	i = 2;
	line++;
	while (*line && *line != start)
	{
		line++;
		printf("ici 2%c\n", *line);
		if (*line == start && *line + 1 && *line + 1 != 32)
			line++;
		i++;
	}
	if (*line == start)
		line++;
	return (i);
}

int	prstwo(char *line, int *en, t_tras *t)
{
	int	end;

	end = *en;
	if ((*line == 39 && *line + 1 != 39) || (*line == 34 && *line + 1 != 34))
	{
		end = test(line, *line);
		if (*line == 39)
			*t = NO;
		else
			*t = YES;
		line += end;
	}
	else if (*line + 1 == 39 && *line + 1 != 34)
		return (2);
	else
	{
		while (*line && *line != 32 && ft_space(*line))
		{
			end++;
			line++;
			*t = YES;
		}
	}
	*en = end;
	return (0);
}

static void	test_pars(char **lines, int *en, t_tras *t)
{
	char	*line;
	int		end;

	end = *en;
	line = *lines;
	while (*line && *line != 32 && !ft_space(*line))
	{
		end++;
		line++;
		if (*line && (*line == 34 || *line == 39) && *line + 1
			&& (*line != 34 || *line != 39))
		{
			end++;
			line++;
		}
		*t = YES;
	}
	*lines = line;
	*en = end;
}

int	pars_cmd(t_list_token *l, char *line, int end)
{
	int		i;
	t_tras	t;

	while (*line != 0)
	{
		end = 0;
		i = 0;
		while (*line && *line == 32)
			line++;
		if (!*line)
			return (SUCCESS);
		if (!ft_space(*line))
			test_pars(&line, &end, &t);
		else
		{
			i = prstwo(line, &end, &t);
			line += i;
			line += end;
		}
		if (add_list(l, line, end, t))
			return (token_clear(l), FAIL);
		line += i;
	}
	return (SUCCESS);
}

int	parsing(char *line, t_list_token *t)
{
	t_list_token	l;

	token_init(&l);
	if (pars_cmd(&l, line, 0) == FAIL && !l.first)
		return (FAIL);
	add_token(l.first);
	if (verification_token(l.first) == FAIL)
		return (token_clear(&l), FAIL);
	t->first = l.first;
	return (SUCCESS);
}
