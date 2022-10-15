/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompteur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:50:52 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/15 14:40:37 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	verification_quote(char *line)
{
	int	start;
	char	c;

	start = 0;
	while (*line)
	{
		if (start == 0  && (*line == 34 || *line == 39))
		{
			c = *line;
			start++;
			line++;
		}
		if (*line && start == 1 && *line == c)
			start = 0;
		line++;
	}
	if (start == 1)
		return (printf("bash: systax error %c\n", c), FAIL);
	return (SUCCESS);
}

void	prompt(/*voir ce qu'il y a pas a passer*/)
{
	char	*line;

	line = readline("doudou > ");
	while (line != NULL)
	{
		if (verification_quote(line))
		{

		}
		parsing(line);
		//ici on envoie la ligne vair le parsing est l'execution du programme
		free(line);
		line = readline("doudou > ");
	}
  //  return (SUCCESS);
}