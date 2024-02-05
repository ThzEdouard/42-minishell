/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:16:17 by eflaquet          #+#    #+#             */
/*   Updated: 2023/01/06 16:08:27 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free2(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	ft_nbwords(char const *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (words);
}

char	*ft_setword(char *testword, char const *s, int len, int i)
{
	int	y;

	y = 0;
	while (len > 0)
	{
		testword[y] = s[i - len];
		y++;
		len--;
	}
	testword[y] = '\0';
	return (testword);
}

char	**ft_words(char **test, int words, char const *s, char c)
{
	int	i;
	int	word;
	int	len;

	i = 0;
	word = 0;
	len = 0;
	while (word < words)
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			len++;
		}
		test[word] = malloc(sizeof(char) * (len + 1));
		if (!test[word])
			return (ft_free2 (test));
		ft_setword (test[word], s, len, i);
		word++;
		len = 0;
	}
	test[word] = 0;
	return (test);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**test;

	if (!s)
		return (NULL);
	words = ft_nbwords (s, c);
	test = malloc (sizeof(char *) * (words + 1));
	if (!test)
		return (0);
	if (!ft_words (test, words, s, c))
		return (NULL);
	return (test);
}
