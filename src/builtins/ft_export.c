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

void	ft_export(t_env **env, char *cmd)
{
	t_env	*tmp;
	int i;
	int ok;

	i = 0;
	ok = 0;
	tmp = *env;
	if (cmd[0] >= '0' && cmd[0] <= '9')
	{
		printf("bash: export: `%s': not a valid identifier\n", cmd);
		return ;
	}
	while(cmd[i])
	{
		if(cmd[i] == '=')
			ok = 1;
		i++;
	}
	if (!ok)
		return ;
	while (tmp->next)
	{
		while(tmp->str && tmp->str[i] != '=')
			i++;
		if(!ft_strncmp(cmd, tmp->str, i))
			return ;
		i = 0;
		tmp = tmp->next;
	}
	tmp->next = new_elem(cmd);
}
