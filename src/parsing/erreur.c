/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erreur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:16:15 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/07 23:08:51 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_quite_error(char s, int len)
{
	char	*str;

	if (len == 2)
	{
		str = ft_strccat(s, s);
		if (!str)
			return ;
		printf(ERROR_0, NAME_SHELL_ERROR, str);
		free (str);

	}
	else
		printf(ERROR_0, NAME_SHELL_ERROR, &s);
}

void	ft_code_error(e_type type, char *str, int len)
{
	if (len == 2)
		printf(ERROR_0_1, NAME_SHELL_ERROR);
	else
	{
		if (type == PIPE || type == APPEND || type == WRITE || type == HEREDOC || type == READ)
			printf(ERROR_0, NAME_SHELL_ERROR, str);
		if (type == DIRECTORY)
			printf(ERROR_1, NAME_SHELL_ERROR, str);
	}
}