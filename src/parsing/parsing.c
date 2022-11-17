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
		i++;
	}
	return (i);
}

void	prstwo(char *line, int *en)
{
	int	end;

	end = *en;
	if (*line == 39 || *line == 34)
	{
		end = test(line, *line);
		line += end;
	}
	else
	{
		while (*line && *line != 32 && ft_space(*line))
		{
			end++;
			line++;
		}
	}
	*en = end;
}

int	pars_cmd(t_list_token *l, char *line, int end)
{
	while (*line)
	{
		end = 0;
		while (*line && *line == 32)
			line++;
		if (!*line)
			return (SUCCESS);
		if (!ft_space(*line))
		{
			while (*line && *line != 32 && !ft_space(*line))
			{
				end++;
				line++;
			}
		}
		else
		{
			prstwo(line, &end);
			line += end;
		}
		if (add_list(l, line, end))
			return (token_clear(l), FAIL);
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
