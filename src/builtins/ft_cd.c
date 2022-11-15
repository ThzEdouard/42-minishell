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

int	ft_cd(t_env **env, char *cmd)
{
	(void)env;
	if (access(cmd, F_OK | X_OK) == -1)
	{
		printf(ERROR_5, NAME_SHELL_ERROR, "cd", cmd);
		return (1);
	}
	if (chdir(cmd) == 1)
	{
		perror("chdir() to failed");
		return (1);
	}
	return (0);
}
