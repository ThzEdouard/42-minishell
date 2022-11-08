/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:01:26 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 22:42:50 by aradice          ###   ########.fr       */
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



char *ft_access(t_exec *exec)
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

char	*ft_path(t_exec *exec, t_env *env)
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
	int i = 0, y = 0;
	new = malloc(sizeof(t_exec));
	if (!new)
		return ;
	new->cmd = malloc(10000);
	
	//printf("%s", new->path_cmd);
	new->filename = malloc(10000);
	while(filename[y])
	{
		new->filename[y] = filename[y];
		y++;
	}
	while(cmd[i])
	{
		new->cmd[i] = cmd[i];
		i++;
	}
	if (env)
	{
		new->path_cmd = ft_path(new, env);
	}
	new->type = type;
	new->prev = l->last;
	new->next = NULL;
	if (l->last)
		l->last->next = new;
	else
		l->first = new;
	l->last = new;
}

void	exec_clear()
{

}