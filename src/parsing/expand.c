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

char	*ft_join_realloc(char *s, int i, int len, char *s2)
{
	char	*value;
	char	*name;

	value = malloc(sizeof(char *) * (i + ft_strlen(s2) - (i - len + 1) + 1));
	if (!value)
		return (NULL);
	ft_strncpy(value, s, len - 2);
	value[len - 2] = 0;
	if (s2)
	{
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
		{
			value = ft_free_strjoin(value, name);
			free(name);
		}
		value = ft_free_strjoin(value, s);
	}
	else
	{
		//printf("\ns == %s  len = %d\n", s, len);
		while (s && *s && len--)
			s++;
		while (s && *s && *s != 36)
			s++;
		if (s && *s)
			value = ft_free_strjoin(value, s);
	}
	return (value);
}

int	update_str(char **str, t_env *env, int i, int len)
{
	char	*name;
	char	*change;

	//printf("name = %s len = %d\n", *str + len - 1,  i - len);
	if (*(*str + len - 1) == 36)
		name = NULL;
	else
	{
		name = get_name(env, *str + len - 1, (i - len + 1));
		//printf("je passe la");
	}

	// if (!name)
	// 	return (printf("fb"), FAIL);
	//printf("len = %d", len);
	change = ft_join_realloc(*str, (i - len), len, name);
	if (!change)
		return (FAIL);
	if (!ft_strncmp(name, "?=", 2))
		free(name);
	free(*str);
	*str = change;
	return (SUCCESS);
}

void	expand_quote(t_list_token *l)
{
	t_token	*tmp;
	int		i;
	char	c;

	tmp = l->first;
	while (tmp)
	{
		c = 0;
		i = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == 34 || tmp->str[i] == 39)
			{
				c = tmp->str[i];
				break ;
			}
			i++;
		}
		expand_quote_2(tmp, c);
		tmp = tmp->next;
	}
}

void	expand_quote_2(t_token	*tmp, char c)
{
	int		i;
	char	*tmp_str;
	int		y;

	if (c != 0)
	{
		tmp_str = malloc(sizeof(char) * (ft_strlen(tmp->str) - 1));
		if (!tmp_str)
			return ;
		i = 0;
		y = 0;
		while (tmp->str[i])
		{
			if (tmp->str[i] == c)
			{
				i++;
				continue ;
			}
			tmp_str[y++] = tmp->str[i++];
		}
		tmp_str[y] = 0;
		free(tmp->str);
		tmp->str = ft_strdup(tmp_str);
		free (tmp_str);
	}
}



void	expand(t_list_token *l, t_env *env)
{
	if (env)
		expand_utils(l, env);
	expand_quote(l);
}
