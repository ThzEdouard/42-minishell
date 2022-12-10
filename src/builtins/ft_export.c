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

void	print_solo(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	add_export(t_env **env, char *cmd, int ok)
{
	char	*test;
	t_env	*tmp;

	tmp = *env;
	test = get_name(*env, cmd, ok);
	if (!test)
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!tmp->next)
			tmp->next = new_elem(cmd);
	}
	else
	{
		while (tmp)
		{
			if (!ft_strncmp(tmp->str, cmd, ok))
			{
				free(tmp->str);
				tmp->str = ft_strdup(cmd);
				break ;
			}
			tmp = tmp->next;
		}
	}
}

void	check_export(t_env **env, char *cmd)
{
	int	i;
	int	ok;

	i = 0;
	ok = 0;
	if ((cmd[0] < 'a' || cmd[0] > 'z')
		&& (cmd[0] < 'A' || cmd[0] > 'Z') && cmd[0] != '_')
	{
		printf("bash: export: `%s': not a valid identifier\n", cmd);
		g_statesssss = 1;
	}
	else
	{
		while (cmd[i])
		{
			if (cmd[i] == '=')
				ok = i;
			i++;
		}
		if (!ok)
			return ;
		i = 0;
		add_export(env, cmd, ok);
		g_statesssss = 0;
	}
}

int	ft_export(t_env **env, char **cmd)
{
	int	y;
	int	i;

	i = 0;
	y = 1;
	while (cmd[i])
		i++;
	if (i == 1)
	{
		print_solo(*env);
		g_statesssss = 0;
		return (SUCCESS);
	}
	while (cmd[y])
	{
		check_export(env, cmd[y]);
		y++;
	}
	return (SUCCESS);
}
