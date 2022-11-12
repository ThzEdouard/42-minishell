/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:53:33 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/15 13:16:40 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

char	*ft_free_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest || !s1 || !s2)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = -1;
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[size] = 0;
	free(s1);
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest || !s1 || !s2)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = -1;
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[size] = 0;
	return (dest);
}
