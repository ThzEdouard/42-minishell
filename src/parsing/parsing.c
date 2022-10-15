/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:28 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/15 15:22:56 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_space(char c)
{
	if (c != 34 && c != 39 && c != 60 && c!= 62)
		return (0);
	return (1);
}

int	test(char *line, char start)
{
	int	i = 2;
	line++;
	while (*line && *line != start)
		line++, i++;
	return (i);
}

void	pars_cmd(t_list_token *l, char *line)
{
	int	end;

	while (*line)
	{
		end = 0;
		while (*line && *line == 32)
		line++;
		if(!ft_space(*line))
		{
			while (*line && *line != 32 &&!ft_space(*line))
				end++, line++;
		}
		else
		{
			if (*line == 39 || *line == 34)
			{
				end = test(line, *line);
				line+=end;
			}
			else{
				while (*line && ft_space(*line))
					end++, line++;
			}
		}
		token_push(l, ft_substr(line-end, 0, end));
	}
}

void View(t_list_token l)
{
	t_token *pelem = l.first;
	while(pelem)
	{
		printf("%s\n",pelem->str);
		pelem = pelem->next;
	}
}

int	parsing(char *line)
{
	t_list_token l;

	token_init(&l);
	pars_cmd(&l, line);
	View(l);
	return (SUCCESS);
}