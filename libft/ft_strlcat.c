/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:35:52 by eflaquet          #+#    #+#             */
/*   Updated: 2022/05/07 16:46:30 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;

	i = 0;
	dest_len = ft_strlen(dst);
	if (dest_len + 1 < size && size > 0)
	{
		while (src[i] && (dest_len + i + 1 < size))
		{
			dst[dest_len + i] = src[i];
			i++;
		}
		dst[dest_len + i] = 0;
	}
	i = ft_strlen(src);
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + i);
}
