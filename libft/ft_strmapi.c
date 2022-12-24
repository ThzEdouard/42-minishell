/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:26:07 by eflaquet          #+#    #+#             */
/*   Updated: 2022/05/07 15:25:09 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		i;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	ptr = (char *)malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (j < i)
	{
		ptr[j] = f(j, s[j]);
		j++;
	}
	ptr[j] = 0;
	return (ptr);
}
