/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompteur.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:50:52 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/07 19:02:50 by eflaquet         ###   ########.fr       */
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
		if (start == 0 && (*line == 59 || *line == 40 || *line == 41 || *line == 92))
		{
			if (start == 0 && (*(line + 1) == 59 || *(line + 1) == 40 || *(line + 1) == 41 || *(line + 1) == 92))
				return (ft_quite_error(*line, 2), FAIL);
			return (ft_quite_error(*line, 1), FAIL);
		}
		if (*line && start == 1 && *line == c)
			start = 0;
		line++;
	}
	if (start == 1)
		return (ft_quite_error(c, 1), FAIL);
	return (SUCCESS);
}


void	prompt(t_env **env, char **envp)
{
	char	*line;
	t_exec *exec;
	t_list_token t;
	t_list_exec e;
	exec_init(&e);
	token_init(&t);
	line = readline("doudou > ");
	while (line != NULL)
	{
		if (verification_quote(line) == SUCCESS && (parsing(line, &t) == SUCCESS))
		{
			exec = add_exec(t.first, *env);
			ft_exec(exec, envp, env);
			token_clear(&t);
			e.first = exec;
			token_clear(&t);
			exec_clear(&e);
		}
		//ici on envoie la ligne vair le parsing est l'execution du programme
		add_history(line);
		free(line);
		line = readline("doudou > ");
	}
  //  return (SUCCESS);
}
