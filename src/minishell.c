/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:23 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/02 14:26:04 by eflaquet         ###   ########.fr       */
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
	(void) argc, (void)argv, (void)envp;
	//gen l'env
	prompt();
	return (SUCCESS);
}