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

//ici on ajoute un type au token pour savoir ce ue sais !!!



//apres avoir atribuet les type il faut verifier si il n'y a pas d'error
//comment verifier les ereur pposible avec les type au niveau des doublon
//verifier en meme temp que on atribut un type ou apres le type
// a voir

int		verification_arg(t_token *t)
{
	while (t->next)
	{
		if (t->type != WORD && t->next->type != WORD)
			return (ft_code_error(t->next->type, t->str, 0), FAIL);
		t = t->next;
	}
	if (t->next == NULL && t->type != WORD && t->type != DIRECTORY)
		return (ft_code_error(t->type, t->str, 0), FAIL);
	return (SUCCESS);
}

int		verification_token(t_token *t)
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
		if (i == 0 && t->type == DIRECTORY)
			return (ft_code_error(DIRECTORY, t->str,0), FAIL);
		t = t->next;
		i++;
	}

	return (SUCCESS);
}

void	add_token(t_token *t)
{
	if (!ft_strncmp(t->str , "|", 1))
		t->type = PIPE;
	else if(!ft_strcmp(t->str, ">"))
		t->type = WRITE;
	else if(!ft_strcmp(t->str, "<"))
		t->type = READ;
	else if(!ft_strncmp(t->str, ">>", 2))
		t->type = APPEND;
	else if(!ft_strncmp(t->str, "<<", 2))
		t->type = HEREDOC;
	else if (!ft_chrdir(t->str))
		t->type = DIRECTORY;
	else
		t->type= WORD;
	t = t->next;
	if (t)
		add_token(t);
}

//apres avoir tout verifier voir comment tout rasemble pour que tout fonctonne bien