/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:23 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/06 19:41:55 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_statesssss;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	
	g_statesssss = 0;
	(void) argc;
	(void) argv;
	generator_env(&env, envp);
	prompt(&env, envp);
	clear_env(&env);
	return (SUCCESS);
}
