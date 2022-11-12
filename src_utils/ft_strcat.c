/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:59:41 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/07 18:45:15 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	dest_len;

	dest_len = ft_strlen(dest);
	i = -1;
	while (src[++i] != '\0')
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*ft_strccat(char c, char t)
{
	char	*str;

	str = malloc(sizeof(char) * 3);
	if (!str)
	{
		return (NULL);
	}
	str[0] = c;
	str[1] = t;
	str[2] = 0;
	return (str);
}
