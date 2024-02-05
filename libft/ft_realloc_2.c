/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ralloc_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:35 by eflaquet          #+#    #+#             */
/*   Updated: 2022/12/09 22:32:06 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_double_len(char **src)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*set_value(char *value, char *name)
{
	value = ft_free_strjoin(value, name);
	free(name);
	return (value);
}

char	*ft_join_realloc(char *s, int i, int len, char *s2)
{
	char	*value;
	char	*name;

	value = malloc(sizeof(char *) * (i + ft_strlen(s2) - (i - len + 1) + 1));
	if (!value)
		return (NULL);
	ft_strncpy(value, s, len);
	value[len] = 0;
	s += len;
	while (s && *s != 36)
		s++;
	if (*s == 36)
		s++;
	while (s2 && *s2 != '=' && *s2 == *s)
	{
		s2++;
		s++;
	}
	name = ft_strdup(s2 + 1);
	if (name)
		value = set_value(value, name);
	value = ft_free_strjoin(value, s);
	return (value);
}
