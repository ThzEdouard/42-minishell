/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 05:37:20 by aradice           #+#    #+#             */
/*   Updated: 2022/11/10 05:37:20 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//a refaire

void	ft_export(t_env **env, char *cmd)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_elem(cmd);
}
