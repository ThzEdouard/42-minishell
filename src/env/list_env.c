/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:38:41 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/03 14:36:10 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*new_elem(char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);
	new->next = NULL;
	return (new);
}


static void	get_env(t_env **env)
{
	char	pwd[255];

	(*env) = new_elem(ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd))));
	(*env)->next = new_elem(ft_strdup("SHLVL=1"));
	(*env)->next->next = new_elem(ft_strdup("_=./minishell"));
}

void	generator_env(t_env **env, char **envp)
{
	int	i;
	t_env	*tmp;

	i = 0;
	if (!envp[i])
	{
		get_env(env);
		return ;
	}
	*env = new_elem(envp[i]);
	tmp = *env;
	i++;
	while (envp[i])
	{
		tmp->next = new_elem(envp[i]);
		tmp = tmp->next;
		i++;
	}
}