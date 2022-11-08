
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
//a finir !
void	exec_init(t_list_exec *l)
{
	l->first = NULL;
	l->last = NULL;
}

void	ft_free_all(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_paths(t_exec *data)
{
	free(data->path);
	ft_free_all(data->cmd);
	exit(1);
}

static char *ft_access(t_exec *exec)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = 0;
	cmd = exec->cmd[0];
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
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
	return (NULL);
}

static char	*ft_path(t_exec *exec, t_env *env)
{
	char	*paths;

	while (env)
	{
		if ((paths = ft_strnstr(env->str, "PATH=", 5)))
		{
			exec->path  = ft_substr(paths, 5, ft_strlen(paths));

			if (!exec->path)
			{
				ft_free_all(exec->cmd);
				exit(1);
			}
			break ;
		}
		env = env->next;
	}
	exec->paths = ft_split(exec->path, ':');
	if (!exec->paths)
		ft_free_paths(exec);
	free(exec->path);
	return (ft_access(exec));
}

void	exec_push(t_list_exec *l, char **cmd, char **filename, e_type type, t_env *env)
{
	t_exec	*new;
	(void)env;
	new = malloc(sizeof(t_exec));
	if (!new)
		return ;
	new->cmd = ft_double_raloc(cmd);
	new->filename = ft_double_raloc(filename);
	if (env)
	{
		new->path_cmd = ft_path(new, env);
	}
	new->file = NULL;
	new->type = type;
	new->prev = l->last;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;

}

void	exec_clear(t_list_exec *l)
{

	t_exec	*tmp;
	t_exec	*elem;

	elem = l->first;
	while (elem)
	{
		tmp = elem;
		ft_free_all(tmp->cmd);
		if (tmp->path_cmd)
			free(tmp->path_cmd);
		ft_free_all(tmp->filename);
		if (tmp->file)
			free(tmp->file);
		elem = elem->next;
		free(tmp);
	}
	l->first = NULL;
	l->last = NULL;
}