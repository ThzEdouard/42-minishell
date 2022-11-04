/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:23 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 19:38:20 by aradice          ###   ########.fr       */
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

	prompt(env, envp);

	//cler ce qu'il y a a clear
	return (SUCCESS);
}