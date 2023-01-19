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

char	*line_prompter(t_env **env, t_list_token t, t_list_exec e)
{
	char	*line;
	t_exec	*exec;
	char	**envp;

	init_sig();
	while (1)
	{
		line = readline("Minishell > ");
		if (!line)
			break ;
		if (ft_strlen(line) && verification_quote(line) == SUCCESS)
		{
			if ((parsing(line, &t, *env) == SUCCESS))
			{
				exec = add_exec(t.first, *env);
				token_clear(&t);
				envp = new_envp(*env);
				line_prompter_2(exec, env, envp);
				e.first = exec;
				exec_clear(&e);
			}
		}
		ft_history_free(line);
	}
	return (line);
}

void	line_prompter_2(t_exec *exec, t_env **env, char **envp)
{
	ft_exec(exec, envp, env);
	if (envp)
		free(envp);
}

void	ft_history_free(char *line)
{
	add_history(line);
	free(line);
}

void	prompter(t_env **env, char **envp)
{
	t_list_token	t;
	t_list_exec		e;
	char			*line;

	(void)envp;
	if (g_statesssss == 130)
		return ;
	exec_init(&e);
	token_init(&t);
	line = line_prompter(env, t, e);
	if (!line)
		ft_putstr_fd("exit\n", 1);
}
