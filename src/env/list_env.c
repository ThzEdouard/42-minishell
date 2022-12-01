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
	if (!new->str)
		return (NULL);
	new->next = NULL;
	return (new);
}

char	*creat_code()
{
	char	*code;
	char	*nbr;

	nbr = ft_itoa(g_statesssss);
	if(!nbr)
		return (NULL);
	code = malloc(sizeof(char) * (3 + ft_strlen(nbr)));
	if (!code)
		return (free(nbr), NULL);
	code = ft_strjoin("?=", nbr);
	return (free(nbr), code);
}

char	*get_name(t_env *env, char *s, int len)
{
	// char	*tmp;
	// t_env	**tmp_env;

	if (!ft_strncmp(ECHO_CODE, s, 1))
	{
		// tmp = creat_code();
		// if (!tmp)
		// 	return (NULL);
		// tmp_env = &env;
		// add_export(tmp_env, tmp, 2);
		// free(tmp);
		return (NULL);
	}
	while (env)
	{
		if (!ft_strncmp(env->str, s, len))
			return (env->str);
		env = env->next;
	}
	return (NULL);
}

void	generator_env(t_env **env, char **envp)
{
	int		i;
	t_env	*tmp;

	i = 0;
	*env = new_elem(envp[i]);
	tmp = *env;
	i++;
	while (envp[i])
	{
		tmp->next = new_elem(envp[i]);
		if (!tmp->next)
		{
			clear_env(env);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}

void	clear_env(t_env **env)
{
	t_env	*envs;

	while (*env)
	{
		envs = *env;
		*env = (*env)->next;
		free(envs->str);
		free(envs);
	}
	*env = NULL;
}
