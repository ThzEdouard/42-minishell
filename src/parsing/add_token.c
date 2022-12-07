/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:45:42 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/07 22:10:09 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	verification_arg(t_token *t)
{
	if (t && t->next && t->type == PIPE)
		return (ft_code_error(t->type, t->str, 0), FAIL);
	if (!t->next && t->type != WORD)
		return (ft_code_error(t->type, t->str, 0), FAIL);
	while (t->next)
	{
		if (t->prev && t->prev->type == WORD && t->type == PIPE && t->next->type != PIPE)
		{
			t = t->next;
			continue ;
		}
		if ((t->type != WORD && t->next->type != WORD))
			return (ft_code_error(t->next->type, t->str, 1), FAIL);
		t = t->next;
	}
	if (t && !t->next && t->type != WORD)
		return (ft_code_error(t->type, t->str, 0), FAIL);
	return (SUCCESS);
}

int	verification_token(t_token *t)
{
	int	i;

	i = 0;
	if (verification_arg(t) == FAIL)
		return (FAIL);
	while (t)
	{
		if (t->type == PIPE && ft_strlen(t->str) > 1)
			return (ft_code_error(PIPE, "||", 0), FAIL);
		if (t->type == APPEND && ft_strlen(t->str) > 2)
			return (ft_code_error(APPEND, ">>", 0), FAIL);
		if (t->type == HEREDOC && ft_strlen(t->str) > 2)
			return (ft_code_error(HEREDOC, "<<", 0), FAIL);
		if(t->type == COUNT)
			return (ft_code_error(COUNT, "&&", 0), FAIL);
		t = t->next;
		i++;
	}
	return (SUCCESS);
}

void	add_token(t_token *t)
{
	if (!ft_strncmp(t->str, "|", 1))
		t->type = PIPE;
	else if (!ft_strcmp(t->str, ">"))
		t->type = WRITE;
	else if (!ft_strcmp(t->str, "<"))
		t->type = READ;
	else if (!ft_strncmp(t->str, ">>", 2))
		t->type = APPEND;
	else if (!ft_strncmp(t->str, "<<", 2))
		t->type = HEREDOC;
	else if (!ft_strncmp(t->str, "&", 1))
		t->type = COUNT;
	else
		t->type = WORD;
	t = t->next;
	if (t)
		add_token(t);
}
