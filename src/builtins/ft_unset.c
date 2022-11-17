/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 05:37:04 by aradice           #+#    #+#             */
/*   Updated: 2022/11/10 05:37:04 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_delete_node(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	env->str = tmp->str;
	env->next = tmp->next;
	tmp->next = NULL;
	free(tmp);
}

void	ft_unset(t_env **env, char *cmd)
{
	t_env	*tmp;
	char	*tmp_str;
	tmp = *env;
	tmp_str = ft_strjoin(cmd, "=");
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, tmp_str, ft_strlen(tmp_str)))
		{

			if (tmp->next)
			{
				ft_delete_node(tmp);printf("coucou\n");
			}

			else
			{
				free(tmp->str);
				tmp->str = NULL;
				//free(tmp);

			}
			break ;
		}
		tmp = tmp->next;
	}
	free(tmp_str);
}
