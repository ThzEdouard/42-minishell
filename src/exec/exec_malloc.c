/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 17:30:59 by aradice           #+#    #+#             */
/*   Updated: 2022/12/12 16:38:07 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	calcul_len_malloc(t_token *tmp, int *len_cmd, int *len_file)
{
	int	file;
	int	cmd;

	file = 0;
	cmd = 0;
	while (tmp)
	{
		if (tmp->type != WORD && tmp->type != PIPE)
		{
			file++;
		}
		else if (tmp->type == WORD)
		{
			cmd++;
		}
		tmp = tmp->next;
	}
	cmd -= file;
	*len_cmd = cmd;
	*len_file = file;
}

int	malloc_cmd_filename(t_token *t, t_add *values)
{
	int	nb_filename;
	int	nb_cmd;

	nb_filename = 0;
	nb_cmd = 0;
	calcul_len_malloc(t, &nb_cmd, &nb_filename);
	if (malloc_command(values, nb_cmd))
		return (FAIL);
	if (!values->filename && nb_filename)
	{
		values->filename = malloc(sizeof(char *) * (nb_filename + 1));
		values->type = malloc(sizeof(t_type) * (nb_filename + 1));
		if (!values->filename || !values->type)
			return (FAIL);
		while (nb_filename)
		{
			values->filename[nb_filename] = 0;
			values->type[nb_filename--] = 0;
		}
		values->filename[nb_filename] = 0;
			values->type[nb_filename] = 0;
	}
	malloc_type(values);
	return (SUCCESS);
}

int	malloc_command(t_add *values, int nb_cmd)
{
	if (!values->command && nb_cmd)
	{
		values->command = malloc(sizeof(char *) * (nb_cmd + 1));
		if (!values->command)
			return (FAIL);
		while (nb_cmd)
			values->command[nb_cmd--] = 0;
		values->command[nb_cmd] = 0;
	}
	return (SUCCESS);
}

void	malloc_type(t_add *values)
{
	if (!values->type)
	{
		values->type = malloc(sizeof(t_type) * 2);
		if (!values->type)
			return ;
		values->type[0] = 0;
	}
}
