/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 20:49:36 by eflaquet          #+#    #+#             */
/*   Updated: 2022/05/07 16:12:47 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2 || n == 0)
		return (0);
	while (*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i)
			&& i + 1 < n)
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}

int	ft_strcmp(char *s1, char *s2)
{
    int	i;

    i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}
