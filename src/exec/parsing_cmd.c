/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 03:16:39 by aradice           #+#    #+#             */
/*   Updated: 2022/10/12 19:29:25 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char	*ft_access(t_exec *data)
// {
// 	int		i;
// 	char	*temp;
// 	char	*temp2;
// 	char	*command;

// 	i = 0;
// 	command = data->cmd[0];
// 	if (access(command, F_OK | X_OK) == 0)
// 		return (command);
// 	while (data->paths[i])
// 	{
// 		temp = ft_strjoin(data->paths[i], "/");
// 		temp2 = ft_strjoin(temp, command);
// 		free(temp);
// 		if (access(temp2, F_OK | X_OK) == 0)
// 		{
// 			ft_free_all(data->paths);
// 			data->command_path = temp2;
// 			return (temp2);
// 		}
// 		free(temp2);
// 		i++;
// 	}
// 	ft_free_all(data->paths);
// 	return (NULL);
// }

// char	*ft_path(t_exec *data, char **envp)
// {
// 	int		i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], "PATH=", 5))
// 		{
// 			data->path = ft_substr(envp[i], i, ft_strlen(envp[i]));
// 			if (!data->path)
// 			{
// 				ft_free_all(data->cmd);
// 				exit(1);
// 			}
// 			break ;
// 		}
// 		i++;
// 	}
// 	data->paths = ft_split(data->path, ':');
// 	if (!data->paths)
// 		ft_free_paths(data);
// 	free(data->path);
// 	return (ft_access(data));
// }

// void	ft_free_paths(t_exec *data)
// {
// 	free(data->path);
// 	ft_free_all(data->cmd);
// 	exit(1);
// }