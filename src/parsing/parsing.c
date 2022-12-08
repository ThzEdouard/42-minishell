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

	i = 0;
	line++;
	while (*line && *line != start)
	{
		line++;
		i++;
	}
	if (*line == start)
		line++;
	return (i);
}

int	prstwo(char *line, int *en)
{
	int	end;
	int	i;
	end = *en;
	if (*line == 39 || *line == 34)
	{
		end = test(line, *line);
		line += end;
		i = 1;
	}
	else
	{
		while (*line && *line != 32 && ft_space(*line))
		{
			end++;
			line++;
		}
		i = 0;
	}
	*en = end;
	return (i);
}

int	pars_cmd(t_list_token *l, char *line, int end)
{
	int	i;
	while (*line != 0)
	{
		end = 0;
		i = 0;
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
			i = prstwo(line, &end);
			line += i;
			line += end;
		}
		if (add_list(l, line, end))
			return (token_clear(l), FAIL);
		line += i;
	}
	return (SUCCESS);
}
void View(t_list_token l)
{
   t_token *pelem = l.first;
   printf("===================\n");
   while(pelem)
   {
     printf("%s  type %d\n",pelem->str, pelem->type);
     pelem = pelem->next;
   }
   printf("=====================\n");
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
	View(l);
	t->first = l.first;
	return (SUCCESS);
}
