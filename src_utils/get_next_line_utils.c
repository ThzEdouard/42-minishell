/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:33:09 by aradice           #+#    #+#             */
/*   Updated: 2022/05/28 19:33:09 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_strchr_gnl(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
}

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*test;
	int		s1size;
	int		s2size;

	s1size = 0;
	s2size = 0;
	test = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!test)
		return (NULL);
	while (s1 && s1[s1size])
	{
		test[s1size] = s1[s1size];
		s1size++;
	}
	while (s2[s2size])
	{
		test[s1size++] = s2[s2size++];
	}
	test[s1size] = '\0';
	free(s1);
	return (test);
}
