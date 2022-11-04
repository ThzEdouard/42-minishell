/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:01:26 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 18:11:41 by eflaquet         ###   ########.fr       */
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



// static char *ft_access(t_exec *exec)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*cmd;

// 	i = 0;
// 	cmd = exec->cmd[0];
// 	if (access(cmd, F_OK | X_OK) == 0)
// 		return (cmd);
// 	while (exec->path->paths[i])
// 	{
// 		tmp = ft_strjoin(exec->path->paths[i], "/");
// 		tmp = ft_free_strjoin(tmp, cmd);
// 		if (access(tmp, F_OK | X_OK) == 0)
// 		{
// 			ft_free_all(exec->path->paths);
// 			exec->path->command_path = tmp;
// 			return (tmp);
// 		}
// 		free(tmp);
// 		i++;
// 	}
// 	return (NULL);
// }

// static char	*ft_path(t_exec *exec, t_env *env)
// {
// 	char	*paths;

// 	while (env)
// 	{
// 		if ((paths = ft_strnstr(env->str, "PATH=", 5)))
// 		{
// 			exec->path->path  = ft_substr(paths, 0, ft_strlen(paths));
// 			if (!exec->path->path)
// 			{
// 				ft_free_all(exec->cmd);
// 				exit(1);
// 			}
// 			break ;
// 		}
// 	}
// 	exec->path->paths = ft_split(exec->path->path, ':');
// 	if (!exec->path->paths)
// 		ft_free_paths(exec);
// 	free(exec->path->path);
// 	return (ft_access(exec));
// }



void	exec_push(t_list_exec *l, char **cmd, char **filename, e_type type, t_env *env)
{
	t_exec	*new;
	(void)env;
	int i = 0, y = 0;
	new = malloc(sizeof(t_exec));
	if (!new)
		return ;
	new->cmd = malloc(10000);
	// if (env)
	// 	new->path_cmd = ft_path(new, env);
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