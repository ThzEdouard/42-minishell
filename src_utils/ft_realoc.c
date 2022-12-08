/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:36:54 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/08 22:26:50 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
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

int	ft_double_len_int(t_type *src)
{
	int	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i])
		i++;
	return (i);
}

int	*ft_realoc_int(char **src)
{
	int	*malloc_src;
	int	i;

	if (!src || ft_double_len(src) == 0)
		return (NULL);
	malloc_src = malloc(sizeof(int) * (ft_double_len(src) + 1));
	if (!malloc_src)
		return (NULL);
	i = ft_double_len(src);
	while (i)
		malloc_src[i--] = 0;
	return (malloc_src);
}

char	**ft_double_raloc(char **src)
{
	int		y;
	char	**malloc_src;
	int		v;

	v = 0;
	y = 0;
	if (!src || ft_double_len(src) == 0)
		return (NULL);
	malloc_src = malloc(sizeof(char *) * (ft_double_len(src) + 1));
	if (!malloc_src)
		return (NULL);
	while (src[v] && !ft_strncmp(src[v], "", 1))
		v++;
	if (src[v])
	{
		while (src[v])
		{
			malloc_src[y++] = ft_strdup(src[v++]);
			while (src[v] && !ft_strncmp(src[v], "", 1))
				v++;
		}
		malloc_src[y] = 0;
		return (malloc_src);
	}
	while (src[y])
	{
		malloc_src[y] = ft_strdup(src[y]);
		y++;
	}
	malloc_src[y] = 0;
	return (malloc_src);
}

t_type	*ft_double_realoc_enum(t_type *src)
{
	int		y;
	t_type	*malloc_src;

	y = 0;
	if (!src || ft_double_len_int(src) == 0)
		return (NULL);
	malloc_src = malloc(sizeof(t_type) * (ft_double_len_int(src) + 1));
	if (!malloc_src)
		return (NULL);
	while (src[y])
	{
		malloc_src[y] = src[y];
		y++;
	}
	malloc_src[y] = 0;
	return (malloc_src);
}
