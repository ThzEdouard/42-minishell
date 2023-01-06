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

int	ft_sep(char line)
{
	if (line == '|' || line == '<' || line == '>' )
		return (SUCCESS);
	return (FAIL);
}

int	pars_quote(char *line, int i)
{
	char	c;

	c = line[i];
	i++;
	while (line[i] && line[i] != c)
		i++;
	c = 0;
	return (i);
}

t_list_token	parsing_line(char *line)
{
	t_list_token	tmp;
	int				i;

	token_init(&tmp);
	while (*line)
	{
		while (*line && *line == 32)
			line ++;
		i = 0;
		while (line[i] && line[i] != 32 && ft_sep(line[i]))
		{
			if (line[i] == 34 || line[i] == 39)
				i = pars_quote(line, i);
			if (line[i] && line[i] != 32)
				i++;
		}
		if (!i)
			while (line[i] && line[i] != 32 && !ft_sep(line[i]))
				i++;
		if (i && add_list(&tmp, line, i))
			return (token_clear(&tmp), tmp);
		line += i;
	}
	return (tmp);
}

int	parsing(char *line, t_list_token *t, t_env *env)
{
	t_list_token	l;

	token_init(&l);
	l = parsing_line(line);
	if (l.first)
	{
		add_token(l.first);
		expand(l.first, env, 0);
		extand(l.first);
		view(l);
		t->first = l.first;
		return (SUCCESS);
	}
	return (FAIL);
}
