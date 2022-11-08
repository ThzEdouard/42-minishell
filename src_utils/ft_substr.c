/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:48:19 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 21:34:48 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

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
	return (ptr);
}