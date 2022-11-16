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
#include <stdio.h>

static int	ft_double_len(char **src)
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

	if (ft_double_len(src) == 0)
		return (NULL);
	malloc_src = malloc(sizeof(int) * (ft_double_len(src) + 1));
	if (!malloc_src)
		return (NULL);
	malloc_src[ft_double_len(src) + 1] = 0;
	return (malloc_src);
}

char	**ft_double_raloc(char **src)
{
	int		y;
	char	**malloc_src;

	y = 0;
	if (!src || ft_double_len(src) == 0)
		return (NULL);
	malloc_src = malloc(sizeof(char *) * (ft_double_len(src) + 1));
	if (!malloc_src)
		return (NULL);
	while (src[y])
	{
		malloc_src[y] = ft_strdup(src[y]);
		y++;
	}
	malloc_src[y] = 0;
	return (malloc_src);
}
