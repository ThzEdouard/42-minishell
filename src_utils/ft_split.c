/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:16:17 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/12 18:22:43 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

static void free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

char	**ft_input(char **tabs, char *s1, char c)
{
	int	len;
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (*s1)
	{
		len = 0;
		while (s1[i] && !(s1[i] == c))
			len++;
		if (len)
		{
			tabs[y] =  malloc(sizeof(char) * (len + 1));
			if (tabs[y])
				return (free_split(tabs), NULL);
			tabs[y] = ft_strncpy(tabs[y], s1, len);
		}
		if (s1[i])
			i++;
	}
	return (tabs);
}

char	**ft_split(char *s1, char c)
{
	char	**str;
	int		wordl;

	wordl = 0;
	if (!s1)
		return (NULL);
	while (*s1)
	{
		while (*s1 != '\0' && (*s1 == c))
			s1++;
		if (*s1 != '\0')
			wordl++;
		while (*s1 != '\0' && !(*s1 == c))
			s1++;
	}
	str = malloc(sizeof(char *) * (wordl + 1));
	if (!str)
		return (NULL);
	str = ft_input(str, s1, c);
	str[wordl] = 0;
	return (str);
}