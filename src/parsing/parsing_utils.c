/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:32:17 by aradice           #+#    #+#             */
/*   Updated: 2023/01/19 18:36:30 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_sep(char line)
{
	if (line == '|' || line == '<' || line == '>' )
		return (SUCCESS);
	return (FAIL);
}

int	pars_quote(char *line, int i)
{
	char	c;

	c = line[i];
	i++;
	while (line[i] && line[i] != c)
		i++;
	c = 0;
	return (i);
}

int	ft_test(char c)
{
	if (c == 32 || (c >= 7 && c <= 13))
		return (1);
	return (0);
}
