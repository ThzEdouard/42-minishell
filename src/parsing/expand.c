/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:48:47 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/06 19:07:14 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_expand(char *str, int i)
{
	while (str[i] && !ft_sep_ex(str[i]))
		i++;
	if (str[i] && str[i] == 39)
	{
		if (str[i] && str[i] == 39)
			i++;
		while (str[i] && str[i] != 39)
			i++;
		if (str[i] && str[i] == 39)
			i++;
	}
	else if (str[i] && str[i] == 34)
	{
		if (str[i] && str[i] == 34)
			i++;
		while (str[i] && str[i] != 36 && str[i] != 34)
			i++;
		if (str[i] && str[i + 1] && str[i - 1] && str[i] == 36
			&& str[i + 1] == '"' && str[i - 1] == '"')
			i++;
		if (str[i] && str[i] == 34)
			i++;
	}
	return (i);
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

char	*rename_expand(char *str, char *tmp_line_env, int i, int y)
{
	char	*tmp_str;

	if (!tmp_line_env)
	{
		while (str[i])
		{
			str[y] = str[i];
			i++;
			y++;
		}
		str[y] = 0;
	}
	else
	{
		tmp_str = ft_join_realloc(str, (y - i), y, tmp_line_env);
		if (!ft_strncmp(tmp_line_env, "?=", 2))
			free(tmp_line_env);
		free(str);
		str = tmp_str;
	}
	return (str);
}

char	*change_expand(char *str, t_env *tmp_e, int *x)
{
	int		i;
	int		y;
	char	*tmp_line_env;

	i = *x;
	y = i;
	i++;
	if (str[i] != '?')
		while (str[i] && (ft_isalpha(str[i])
				|| ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	else
		i++;
	tmp_line_env = get_name(tmp_e, str + (y + 1), i - (y + 1));
	str = rename_expand(str, tmp_line_env, i, y);
	i = 0;
	*x = i;
	return (str);
}

void	expand(t_token *t, t_env *env, int i)
{
	t_env	*tmp_e;
	t_token	*tmp_t;

	tmp_t = t;
	tmp_e = env;
	while (tmp_t)
	{
		if (tmp_t->type == WORD)
		{
			i = check_expand(tmp_t->str, i);
			if (tmp_t->str[i] && tmp_t->str[i] == 36)
				tmp_t->str = expand_util(tmp_t->str, i, tmp_e);
		}
		if (!tmp_t->str[i] || !tmp_t->str[i + 1] || tmp_t->type != WORD)
		{
			tmp_t = tmp_t->next;
			i = 0;
		}
	}
}
