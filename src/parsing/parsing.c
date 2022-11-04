/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:41:28 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 18:09:58 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//faie un viewer pour qu'il affiche les commenande comme personne hihi

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
//voir comment ameliorer cette fonction pour que'elle sois beaucoupe mieux pour la suite
//du parsing avec exec
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
				line += end;
			}
			else{

				while (*line && *line != 32 && ft_space(*line))
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

void view_commande(t_list_token l)
{
	int i;
	t_token *t = l.first;
	while (t)
	{
		i = 0;
		printf("\ncommande : %s", t->str);
		while (t->next  && t->next->type == WORLD)
		{
			t = t->next;
			printf(" arguments %d : %s ", i, t->str);
			i++;
		}
		if (t->next && t->next->type != WORLD)
		{
		    t = t->next;
		    printf ("token : %s", t->str);
		}
		 if (t)
		    t = t->next;
	}
	printf ("\n");
}

void ft_view_groups(t_exec *p)
{

   while(p)
   {
     printf("Command: %s\n Options: %s\n Args: %s\n Type: %d\n File1: %s\n File2: %s\n File3: %s\n File4: %s\n",p->cmd[0], p->cmd[1], p->cmd[2], p->type, p->filename[0], p->filename[1], p->filename[2], p->filename[3]);
    //  printf("Command: %s\n Options: %s\n Args: %s\n Type: %d\n",p->command[0], p->command[1], p->command[2], p->type);
    //  printf("Command: %s\nType: %d\n",p->command[0], p->type);
     p = p->next;
   }

}

//la fonction parsing qui fait tout
int	parsing(char *line, t_list_exec e)
{
	t_list_token l;
	t_exec *exec;
	(void)e;
	token_init(&l);
	pars_cmd(&l, line);
	add_token(l.first);
	if (verification_token(l.first) == FAIL)
		printf("gros fail sa mere ;");
	//view_commande(l);
	exec = add_exec(l.first);
	ft_view_groups(exec);
	//rassenbler les commande apres le parsing quand il est fini
	//View(l);
	// return (FAIL);
	return (SUCCESS);
}