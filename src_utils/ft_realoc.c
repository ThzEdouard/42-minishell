/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:36:54 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/08 15:12:22 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

static int ft_double_len(char **src)
{
	int	i;
	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	**ft_double_raloc(char **src)
{
	int y = 0;
	char	**malloc_src = malloc(sizeof(char *) * (ft_double_len(src)));

	if (!malloc_src || ft_double_len(src) == 0)
		return (NULL);
	while(src[y])
	{
		malloc_src[y] = src[y];
		y++;
	}
	return (malloc_src);
}