/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erreur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:16:15 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/07 23:08:51 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_quit_error(char s, int len)
{
	(void)s;
	if (s == 92)
	{
		printf(ERROR_2);
		g_statesssss = 127;
		return ;
	}
	else if (len == 2)
	{
		printf(ERROR_0, NAME_SHELL_ERROR);
	}
	else
		printf(ERROR_0, NAME_SHELL_ERROR);
	g_statesssss = 2;
}

void	ft_code_error(t_type type, char *str, int len)
{
	(void)str;
	if (len == 0 && type != PIPE)
		printf(ERROR_3, NAME_SHELL_ERROR);
	else
	{
		printf(ERROR_0, NAME_SHELL_ERROR);
		g_statesssss = 2;
		return ;
	}
	 if (len == 1 && type != WORD)
		printf(ERROR_0, NAME_SHELL_ERROR);
	g_statesssss = 2;
}

void	ft_error(char *error)
{
	perror(error);
	exit (1);
}

void	ft_message(char *error, t_exec *data, t_env **env, int code)
{
	ft_putstr_fd(error, 2);
	clear_env(env);
	(void)data;
	exit(code);
}
