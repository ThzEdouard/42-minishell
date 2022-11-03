/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:23 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/03 15:24:18 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


//ATTENTION A FAIRE RAPIDEMENT
//LE MAKEFILE en bien mieux que ce qu'il y a
//actulement pour qu'il sois plus simple d'utilistion
//||||||||!!!!!!!!\\\/
//cree un code erreur pour avoir le erreur bien ecrie est styler

int main(int argc, char **argv, char **envp)
{
	(void) argc, (void)argv;
	t_env	*env;
	generator_env(&env, envp);

	prompt(env);

	//cler ce qu'il y a a clear
	return (SUCCESS);
}