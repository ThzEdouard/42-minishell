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

	g_statesssss = chdir(cmd);
    if (g_statesssss < 0)
        g_statesssss *= -1;
    if (g_statesssss != 0)
        ft_putstr_fd(strerror(errno),  2);
	return (0);
}
