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

static int	verifcation_qot(int *start, char *line)
{
	if (*start == 0 && (*line == 59 || *line == 40
			|| *line == 41))
	{
		if (start == 0 && (*(line + 1) == 59 || *(line + 1) == 40
				|| *(line + 1) == 41))
			return (ft_quite_error(*line, 2), FAIL);
		return (ft_quite_error(*line, 1), FAIL);
	}
	return (SUCCESS);
}

static int	verification_quote(char *line)
{
	int		start;
	char	c;

	start = 0;
	if (ft_strlen(line) == 1 && (*line == ':' || *line == '!'))
		return (FAIL);
	while (*line == '#' ||*line == '\f' || *line == '\n' || *line == '\r' || *line == '\t' || *line == '\v' || *line == ' ')
		line++;
	if (!ft_strlen(line))
		return (FAIL);
	while (*line)
	{
		if (start == 0 && (*line == 34 || *line == 39))
		{
			c = *line;
			start++;
			line++;
		}
		if (verifcation_qot(&start, line) == FAIL)
			return (FAIL);
		if (*line && start == 1 && *line == c)
			start = 0;
		line++;
	}
	if (start == 1)
		return (ft_quite_error(c, 1), FAIL);
	return (SUCCESS);
}

static int	up_code(char *line)
{
	if (!ft_strlen(line))
		return (0);
	if (*line == '!')
		return (1);
	return (0);
}
void View_ex(t_list_token l)
{
   t_token *pelem = l.first;
   printf("===========Ext========\n");
   while(pelem)
   {
     printf("%s  type %d tras  = %d\n",pelem->str, pelem->type, pelem->tras);
     pelem = pelem->next;
   }
   printf("=====================\n");
}
char	*line_prompt(t_env **env, char **envp, t_list_token t, t_list_exec e)
{
	char	*line;
	t_exec	*exec;

	line = readline("doudou > ");
	while (line != NULL)
	{
		if (ft_strlen(line) && verification_quote(line) == SUCCESS)
		{
			if ((parsing(line, &t) == SUCCESS))
			{
				expand(&t, *env);
				View_ex(t);
				exec = add_exec(t.first, *env);
				token_clear(&t);
				ft_exec(exec, envp, env);
				e.first = exec;
				exec_clear(&e);
			}
		}else
			g_statesssss = up_code(line);
		add_history(line);
		free(line);
		line = readline("doudou > ");
	}

	return (line);
}

void	prompt(t_env **env, char **envp)
{
	t_list_token	t;
	t_list_exec		e;
	char			*line;

	if (g_statesssss == 130)
		return ;
	exec_init(&e);
	token_init(&t);
	line = line_prompt(env, envp, t, e);
	if (!line)
		printf("exit\n");
}
