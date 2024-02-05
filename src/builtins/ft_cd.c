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

static void	msg_error(char **args)
{
	if (args[2])
		return (ft_putendl_fd("too many arguments", 2));
	return (ft_putendl_fd(strerror(errno), 2));
}

static int	get_home(t_env **env)
{
	char	*home;

	home = get_name(*env, "HOME", ft_strlen("HOME"));
	if (!home)
		return (ft_putendl_fd("HOME not set", 2), 1);
	g_statesssss = chdir(home + 5);
	if (g_statesssss < 0)
		g_statesssss *= -1;
	if (g_statesssss != 0)
		return (ft_putendl_fd(strerror(errno), 2), 1);
	return (0);
}

int	ft_cd(t_env **env, char **cmd)
{
	if (!cmd[1])
		return (get_home(env));
	if (cmd[2])
		return (msg_error(cmd), 1);
	g_statesssss = chdir(cmd[1]);
	if (g_statesssss < 0)
		g_statesssss *= -1;
	if (g_statesssss != 0)
		msg_error(cmd);
	return (0);
}
