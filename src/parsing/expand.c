/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:32:45 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/17 12:31:51 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_joinralo(char *s, int i, int len, char *s2)
{
	char	*value;
	char	*name;

	value = malloc(sizeof(char *) * (i + ft_strlen(s2) - (i - len + 1) + 1));
	if (!value)
		return (NULL);
	ft_strncpy(value, s, len - 2);
	value[len - 2] = 0;
	s += len + i;
	name = ft_strdup(s2 + i + 2);
	if (name)
	{
		value = ft_free_strjoin(value, name);
		free(name);
	}
	value = ft_free_strjoin(value, s);
	return (value);
}

int	update_str(char **str, t_env *env, int i, int len)
{
	char	*name;
	char	*change;

	name = get_name(env, *str + len - 1, i - len + 1);
	if (!name)
		return (FAIL);
	change = ft_joinralo(*str, (i - len), len, name);
	if (!change)
		return (FAIL);
	free(*str);
	*str = change;
	if (!ft_strncmp(name, "?=", 2))
		free(name);
	return (SUCCESS);
}

void	expand(t_list_token *l, t_env *env)
{
	expand_utils(l, env);
}
