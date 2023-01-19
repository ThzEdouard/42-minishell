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

#include "../include/minishell.h"

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

int	*ft_realloc_int(char **src)
{
	int	*malloc_src;
	int	i;

	if (!src || ft_double_len(src) == 0)
		return (NULL);
	malloc_src = (int *)malloc(sizeof(int) * (ft_double_len(src) + 1));
	if (!malloc_src)
		return (NULL);
	i = ft_double_len(src);
	while (i)
		malloc_src[i--] = 0;
	malloc_src[i] = 0;
	return (malloc_src);
}

char	**ft_double_realloc(char **src)
{
	char	**malloc_src;

	if (!src || ft_double_len(src) == 0)
		return (NULL);
	malloc_src = malloc(sizeof(char *) * (ft_double_len(src) + 1));
	if (!malloc_src)
		return (NULL);
	return (ft_double_realloc_2(src, malloc_src));
}

char	**ft_double_realloc_2(char **src, char **malloc_src)
{
	int		y;
	int		v;

	v = 0;
	y = 0;
	while (src[v] && !ft_strncmp(src[v], "", 1))
		v++;
	while (src[y])
	{
		malloc_src[y] = ft_strdup(src[y]);
		y++;
	}
	malloc_src[y] = 0;
	return (malloc_src);
}

t_type	*ft_double_realloc_enum(t_type *src)
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
