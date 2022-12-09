/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:01:26 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/08 15:00:24 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_paths(t_exec *data)
{
	free(data->path);
	data->path = NULL;
	data->paths = NULL;
	exit(1);
}

static char	*ft_access(t_exec *exec)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = 0;
	cmd = exec->cmd[0];
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_free_all(exec->paths), cmd);
	while (exec->paths[i])
	{
		tmp = ft_strjoin(exec->paths[i], "/");
		tmp = ft_free_strjoin(tmp, cmd);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			ft_free_all(exec->paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	ft_free_all(exec->paths);
	return (NULL);
}

static char	*ft_path(t_exec *exec, t_env *env)
{
	char	*paths;

	while (env)
	{
		paths = ft_strnstr(env->str, "PATH=", 5);
		if (paths)
		{
			exec->path = ft_substr(paths, 5, ft_strlen(paths));
			if (!exec->path)
			{
				ft_free_all(exec->cmd);
				exit(1);
			}
			break ;
		}
		env = env->next;
	}
	if (env)
		exec->paths = ft_split(exec->path, ':');
	if (!exec->paths)
		ft_free_paths(exec);
	free(exec->path);
	return (ft_access(exec));
}

t_exec	*set_path(t_exec *t, t_env *env)
{
	t_exec	*tmp;

	tmp = t;
	while (tmp)
	{
		if (!tmp->path_cmd && tmp->cmd)
			tmp->path_cmd = ft_path(tmp, env);
		tmp = tmp->next;
	}
	return (t);
}
