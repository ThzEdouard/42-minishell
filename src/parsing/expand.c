/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:48:47 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/06 16:17:24 by eflaquet         ###   ########.fr       */
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

void	expand(t_token *t, t_env *env)
{
	t_env	*tmp_env;
	t_token	*tmp_token;
	int		i;
	int		y;
	char	*tmp_line_env;
	char	*tmp_str;

	tmp_token = t;
	tmp_env = env;
	i = 0;
	while (tmp_token)
	{
		if (tmp_token->type == WORD)
		{
			i = check_expand(tmp_token->str, i);
			if (tmp_token->str[i] && tmp_token->str[i] == 36)
			{
				if (tmp_token->str[i + 1] && !ft_isalpha(tmp_token->str[i + 1]) && tmp_token->str[i + 1] == '$' && (tmp_token->str[i + 1] != '_' || tmp_token->str[i + 1] != '?'))
				{
					y = i;
					i++;
					if (tmp_token->str[i] && (!ft_isalpha(tmp_token->str[i]) || tmp_token->str[i] != '$' || tmp_token->str[i] != '"' || tmp_token->str[i] != '\''))
						i++;
					while (tmp_token->str[i])
					{
						tmp_token->str[y] = tmp_token->str[i];
						i++;
						y++;
					}
					tmp_token->str[y] = 0;
					i = 0;
				}
				else if (tmp_token->str[i + 1])
				{
					y = i;
					i++;
					if (tmp_token->str[i] != '?')
						while (tmp_token->str[i] && (ft_isalpha(tmp_token->str[i]) || ft_isalnum(tmp_token->str[i]) || tmp_token->str[i] == '_'))
							i++;
					else
						i++;
					tmp_line_env = get_name(tmp_env, tmp_token->str + (y + 1), i - (y + 1));
					if (!tmp_line_env)
					{
							while (tmp_token->str[i])
						{
							tmp_token->str[y] = tmp_token->str[i];
							i++;
							y++;
						}
						tmp_token->str[y] = 0;
					}
					else
					{
						tmp_str = ft_join_realloc(tmp_token->str, (y - i), y, tmp_line_env);
						if (!ft_strncmp(tmp_line_env, "?=", 2))
							free(tmp_line_env);
						free(tmp_token->str);
						tmp_token->str = tmp_str;
					}
					i = 0;
				}
			}
		}else
			tmp_token = tmp_token->next;
		if (!tmp_token->str[i] || !tmp_token->str[i + 1])
        {
			tmp_token = tmp_token->next;
			i = 0;
		}

	}
}
