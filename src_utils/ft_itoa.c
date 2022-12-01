/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:55:24 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/17 11:56:22 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}

int	ft_intlen(int nb)
{
	int	result;

	result = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		result++;
		nb *= -1;
	}
	while (nb != 0)
	{
		result++;
		nb /= 10;
	}
	return (result);
}

int	abs(int value)
{
	if (value < 0)
		value = -value;
	return (value);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		count;
	int		i;

	count = ft_intlen(n);
	i = 0;
	result = (char *)ft_calloc((count + 1), sizeof(char));
	if (!result)
		return (NULL);
	if (n < 0)
		result[i++] = '-';
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[--count] = abs((n % 10)) + '0';
		n = n / 10;
	}
	return (result);
}
