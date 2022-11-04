/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompteur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:50:52 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 21:08:10 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//la verification des quote est bon voir ausssi pour rajouter les \ est les ; car error pour le doudou

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
		// if (start == 0 && (*line == 59 || line == 40 || *line == 41 ||))//ajouter les \ ;
		// 	return (FAIL);
		if (*line && start == 1 && *line == c)
			start = 0;
		line++;
	}
	if (start == 1)
		return (printf("bash: systax error %c\n", c), FAIL);
	return (SUCCESS);
}


void	prompt(t_env *env, char **envp)
{
	char	*line;
	t_list_exec exec;
	exec_init(&exec);
	line = readline("doudou > ");
	while (line != NULL)
	{
		if (verification_quote(line))
		{
		//apres le parsing on peut preparer pour l'execution qui est important a voir tres rapidemant pour faire plus de test
		}
		parsing(line, exec, envp, env);
		//ici on envoie la ligne vair le parsing est l'execution du programme
		add_history(line);
		free(line);
		line = readline("doudou > ");
	}
  //  return (SUCCESS);
}
