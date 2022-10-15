/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:45:42 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/15 19:35:10 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//ici on ajoute un type au token pour savoir ce ue sais !!!



//apres avoir atribuet les type il faut verifier si il n'y a pas d'error
//comment verifier les ereur pposible avec les type au niveau des doublon
//verifier en meme temp que on atribut un type ou apres le type
// a voir

int		verification_token(t_token *t)
{
	while (t)
	{
		if (t->type == PIPE && ft_strlen(t->str) > 1)
			return (/*voir message error pour le fail*/FAIL);
		if (t->type == APPEND && ft_strlen(t->str) > 2)
			return (FAIL);
		if (t->type == HEREDOC && ft_strlen(t->str) > 2)
			return (FAIL);
		t = t->next;
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
	else
		t->type= WORLD;
	t = t->next;
	if (t)
		add_type(t);
}

//apres avoir tout verifier voir comment tout rasemble pour que tout fonctonne bien