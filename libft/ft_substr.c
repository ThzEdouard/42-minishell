/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:42:33 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/06 16:10:25 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	j = 0;
	if (!s)
		return (NULL);
	i = ft_strlen((char *)s);
	if (start > i)
		start = i;
	if (len > i - start)
		len = i - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (j < len && start + j <= i && s[start + j])
	{
		ptr[j] = s[start + j];
		j++;
	}
	ptr[j] = 0;
	free(s);
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	j = 0;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start > i)
		start = i;
	if (len > i - start)
		len = i - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (j < len && start + j <= i && s[start + j])
	{
		ptr[j] = s[start + j];
		j++;
	}
	ptr[j] = 0;
	return (ptr);
}
