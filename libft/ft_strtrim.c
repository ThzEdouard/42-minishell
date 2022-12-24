/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:00:47 by eflaquet          #+#    #+#             */
/*   Updated: 2022/05/07 18:03:59 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len;
	char		*ptr;
	size_t		i;

	len = ft_strlen(s1);
	i = 0;
	while (ft_strchr(set, (int)s1[i]))
		i++;
	while (ft_strrchr(set, (int)s1[len]))
		len--;
	ptr = ft_substr(s1, i, (len - i + 1));
	if (!ptr)
		return (NULL);
	return (ptr);
}
