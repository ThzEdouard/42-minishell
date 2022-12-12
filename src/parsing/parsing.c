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

int	parse_3(char **lines, int end, t_trace *t)
{
	char	*line;

	line = *lines;
	while (*line && *line != 32 && ft_space(*line))
	{
		end++;
		line++;
		*t = YES;
		if (*line && (*line == '|' || *line == '"' || *line == '\''))
			break ;
	}
	*lines = line;
	return (end);
}

int	parse_2(char *line, int *en, t_trace *t)
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
		end = parse_3(&line, end, t);
	}
	*en = end;
	return (0);
}

int	parse_cmd(t_list_token *l, char *line, int end)
{
	int		i;
	t_trace	t;

	while (*line != 0)
	{
		end = 0;
		i = 0;
		while (*line && *line == 32)
			line++;
		if (!*line)
			return (SUCCESS);
		if (!ft_space(*line))
			test_parse(&line, &end, &t);
		else
		{
			printf("ets o\n %s", line);
			i = parse_2(line, &end, &t);
			line += i;
			line += end;
		}
		if (add_list(l, line, end, t))
			return (token_clear(l), FAIL);
		line += i;
	}
	return (SUCCESS);
}

void	view(t_list_token t)
{
	t_token	*token;

	token = t.first;
	printf("================\n");
	while (token)
	{
		printf("str = '%s'  type = '%d'\n", token->str, token->type);
		token = token->next;
	}
	printf("================\n");
}

int	parsing(char *line, t_list_token *t)
{
	t_list_token	l;

	token_init(&l);
	if (parse_cmd(&l, line, 0) == FAIL && !l.first)
		return (FAIL);
	add_token(l.first);
	view(l);
	if (verification_token(l.first) == FAIL)
		return (token_clear(&l), FAIL);
	t->first = l.first;
	return (SUCCESS);
}
