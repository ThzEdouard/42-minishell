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
			|| *line == 41 || *line == 92))
	{
		if (start == 0 && (*(line + 1) == 59 || *(line + 1) == 40
				|| *(line + 1) == 41 || *(line + 1) == 92))
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

void	prompt(t_env **env, char **envp)
{
	char			*line;
	t_exec			*exec;
	t_list_token	t;
	t_list_exec		e;
	struct sigaction	sa;
	sa.sa_sigaction = sig_int;
	sa.sa_flags = SA_SIGINFO;
	struct sigaction	se;
	
	if (g_statesssss == 130)
		return;
	se.sa_sigaction = sig_quit;
	se.sa_flags = SA_SIGINFO;
	exec_init(&e);
	token_init(&t);
	
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &se, NULL);
	line = readline("doudou > ");
	while (line != NULL)
	{
		
		if (ft_strlen(line) && verification_quote(line) == SUCCESS
			&& (parsing(line, &t) == SUCCESS))
		{
			expand(&t, *env);
			exec = add_exec(t.first, *env);
			token_clear(&t);
			ft_exec(exec, envp, env);
			e.first = exec;
			exec_clear(&e);
		}
		// printf("code error = %d\n", g_statesssss);
		add_history(line);
		free(line);
		line = readline("doudou > ");
	}
}
