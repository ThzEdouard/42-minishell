/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:58:14 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/11 17:14:28 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_env(t_env **env, char *tmp_pwd)
{
	char	pwd[250];
	t_env	*tmp;
	t_env	*tmp_two;
	t_env	*tmp_tree;

	tmp = *env;
	tmp_two = *env;
	tmp_tree = *env;

	while (tmp && ft_strncmp(tmp->str, "PWD=", 4))
		tmp = tmp->next;
	free(tmp->str);

	tmp->str = ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd)));
	printf("aaaa%s",tmp->str);
	while (tmp_two && ft_strncmp(tmp_two->str, "OLDPWD=", 7))
		tmp_two = tmp_two->next;
	if (!tmp_two)
	{
		while (tmp_tree->next)
			tmp_tree = tmp_tree->next;
		tmp_tree->next = new_elem(ft_strjoin("OLDPWD=", tmp_pwd));
		tmp_tree = tmp_tree->next;
	 	return ;
	}
	free(tmp_two->str);
	tmp_two->str = ft_strjoin("OLDPWD=", tmp_pwd);
}

int	ft_cd(t_env **env, char *cmd)
{

	char	tmp_pwd[250];

	getcwd(tmp_pwd, sizeof(tmp_pwd));
	if (chdir(cmd) == 1)
	{
		perror("chdir() to failed");
		return (1);
	}
	else
	{
		set_env(env, tmp_pwd);
	}
	return (0);
}