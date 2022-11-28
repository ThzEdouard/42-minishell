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

// void	ft_check_export(t_env **env, char **cmd)
// {

// }


static void	print_solo(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	ft_export(t_env **env, char **cmd)
{
	t_env	*tmp;
	int 	i;
	int 	y;
	int 	ok;
	char 	*test;

	i = 0;
	y = 1;
	ok = 0;
	while(cmd[i])
		i++;
	if (i == 1)
	{
		print_solo(*env);
		return ;
	}
		
	while (cmd[y])
	{
		i = 0;
		tmp = *env;
		if ((cmd[y][0] < 'a' || cmd[y][0] > 'z') && (cmd[y][0] < 'A' || cmd[y][0] > 'Z') && cmd[y][0] != '_')
		{
			printf("bash: export: `%s': not a valid identifier\n", cmd[1]);
		}
		else
		{
			while(cmd[y][i])
			{
				if(cmd[y][i] == '=')
					ok = i;
				i++;
			}
			if (!ok)
				return ;
			i = 0;
			test = get_name(*env, cmd[y], ok);
			if (!test)
			{
				while (tmp->next)
					tmp = tmp->next;
				if (!tmp->next)
					tmp->next = new_elem(cmd[y]);
			}
			else
			{
				while (tmp)
				{
					if (!ft_strncmp(tmp->str, cmd[y], ok))
					{
						free(tmp->str);
						tmp->str = ft_strdup(cmd[y]);
						//free(cmd[y]);
						break ;
					}
					tmp = tmp->next;
				}
			}

		}
		y++;
		ok = 0;
	}
}
