/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:28 by eflaquet          #+#    #+#             */
/*   Updated: 2022/10/15 22:28:01 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//petite fonction mais tres interesante
int	ft_space(char c)
{
	if (c != 34 && c!= 39 && c != 60 && c!= 62 && c!= 124)
		return (0);
	return (1);
}
//le test fonction voir pour ameliorer tout ca !!
int	test(char *line, char start)
{
	int	i = 2;
	line++;
	while (*line && *line != start)
		line++, i++;
	return (i);
}
//le decoupage est bon a voir il faut attribuer les token avec est return les cas error
void	pars_cmd(t_list_token *l, char *line)
{
	int	end;

	while (*line)
	{
		end = 0;
		while (*line && *line == 32)
			line++;
		if(!ft_space(*line))
		{
			while (*line && *line != 32 && !ft_space(*line))
				end++, line++;
		}
		else
		{
			if (*line == 39 || *line == 34)
			{
				end = test(line, *line);
				line+=end;
			}
			else{

				while (*line  && *line != 32 && ft_space(*line))
					end++, line++;
			}
		}
		token_push(l, ft_substr(line-end, 0, end));
	}
}
//foncction jusste la pour voir a la fin elle degage
void View(t_list_token l)
{
	t_token *pelem = l.first;
	while(pelem)
	{
		printf("%s\n",pelem->str);
		pelem = pelem->next;
	}
}
//la fonction parsing qui fait tout
int	parsing(char *line)
{
	t_list_token l;

	token_init(&l);

	pars_cmd(&l, line);
	add_token(l.first);
	if (verification_token(l.first) == FAIL)
		printf("gros fail sa mere ;");
	// mView(l);
	// return (FAIL);
	return (SUCCESS);
}