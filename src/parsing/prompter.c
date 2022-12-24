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

char	*line_prompter(t_env **env, char **envp, t_list_token t, t_list_exec e)
{
	char	*line;
	t_exec	*exec;

	while (1)
	{
		init_sig();
		line = readline("Minishell > ");
		if (!line)
			break ;
		if (ft_strlen(line) && verification_quote(line) == SUCCESS)
		{
			if ((parsing(line, &t, *env) == SUCCESS))
			{
				exec = add_exec(t.first, *env);
				token_clear(&t);
				ft_exec(exec, envp, env);
				e.first = exec;
				exec_clear(&e);
			}
		}
		add_history(line);
		free(line);
	}
	return (line);
}

void	prompter(t_env **env, char **envp)
{
	t_list_token	t;
	t_list_exec		e;
	char			*line;

	if (g_statesssss == 130)
		return ;
	exec_init(&e);
	token_init(&t);
	line = line_prompter(env, envp, t, e);
	if (!line)
		ft_putstr_fd("exit\n", 1);
}
