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

t_list_token	parsing_line(char *line, int i)
{
	t_list_token	tmp;

	token_init(&tmp);
	while (*line)
	{
		while (*line && ft_test(*line))
			line ++;
		i = 0;
		while (line[i] && !ft_test(line[i]) && ft_sep(line[i]))
		{
			if (line[i] == 34 || line[i] == 39)
				i = pars_quote(line, i);
			if (line[i] && (line[i] != 32 || (line[i] >= 7 && line[i] <= 13)))
				i++;
			else
				break ;
		}
		if (!i)
			while (line[i] && !ft_test(line[i]) && !ft_sep(line[i]))
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
	int				i;

	i = 0;
	token_init(&l);
	l = parsing_line(line, i);
	if (l.first)
	{
		add_token(l.first);
		expand(l.first, env, 0);
		extand(l.first);
		if (verification_token(l.first) == FAIL)
			return (token_clear(&l), FAIL);
		t->first = l.first;
		return (SUCCESS);
	}
	return (FAIL);
}

char	*expand_util(char *str, int i, t_env *tmp_e)
{
	if (str[i + 1] && !ft_isalpha(str[i + 1])
		&& str[i + 1] == '$'
		&& (str[i + 1] != '_' || str[i + 1] != '?'))
		str = check_arg_expand(str, &i);
	else if (str[i + 1])
		str = change_expand(str, tmp_e, &i);
	return (str);
}

char	*check_arg_expand(char *str, int *x)
{
	int	y;
	int	i;

	i = *x;
	y = i;
	i++;
	if (str[i] && (!ft_isalpha(str[i]) || str[i] != '$'
			|| str[i] != '"' || str[i] != '\''))
		i++;
	while (str[i])
	{
		str[y] = str[i];
		i++;
		y++;
	}
	str[y] = 0;
	i = 0;
	*x = i;
	return (str);
}
