/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:10:10 by aradice           #+#    #+#             */
/*   Updated: 2022/11/03 14:09:57 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_strnstr(const char *big, const char *little, size_t size)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < size)
	{
		y = 0;
		while (little[y] && big[i + y] == little[y] && i + y < size)
		{
			if (little[y + 1] == '\0')
				return ((char *)big + i);
			y++;
		}
		i++;
	}
	return (NULL);
}