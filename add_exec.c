/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradice <aradice@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 21:24:03 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/04 21:06:29 by aradice          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	calcul_len_malloc(t_token *tmp, int *len_cmd, int *len_file)
{
	int	file = 0;
	int	cmd = 0;
	while(tmp)
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

static void	cmd_word(t_list_exec *exec, t_token *t,char ***cmd, char ***filename, int *x,t_env *env)
{
	int i = 0;
	int	y = *x;

	*cmd[y] = t->str;
	y++;
	if (!(t->next) || t->next->type == PIPE || t->type == PIPE)
	{
		*cmd[y] = 0;
		exec_push(exec, *cmd, *filename, WORD, env);
		i = 0;
		while(*cmd[i])
		{
			*cmd[i] = 0;
			i++;
		}
		i = 0;
		y = 0;
	}
	*x = y;
}

static void	cmd_write(t_list_exec *exec, t_token *t,char ***cmd, char ***filename, int *x,t_env *env)
{
	int j = *x;
	*filename[j++] = t->next->str;
	while(t->next->next && t->next->next->type == WRITE)
	{
		t = t->next->next;
		*filename[j] = t->next->str;
		j++;
	}
	exec_push(exec, *cmd, *filename, WRITE, env);
	j = 0;
	while(*filename[j])
	{
		*filename[j] = 0;
		j++;
	}
	*x = j;
}

static void cmd_apprent(t_list_exec *exec, t_token *t,char ***cmd, char ***filename, int *x,t_env *env)
{
	int j = *x;
	*filename[j++] = t->next->str;
	while(t->next->next && t->next->next->type == WRITE)
	{
		t = t->next->next;
		*filename[j] = t->next->str;
		j++;
	}
	exec_push(exec, *cmd, *filename, APPEND, env);
	j = 0;
	while(*filename[j])
	{
		*filename[j] = 0;
		j++;
	}
	*x = j;
}

static void	cmd_read(t_list_exec *exec, t_token *t,char ***cmd, char ***filename, int *x,t_env *env)
{
	j = 0;
	*filename[j++] = t->next->str;
	while(t->next->next && t->next->next->type == WRITE)
	{
		t = t->next->next;
		*filename[j] = t->next->str;
		j++;
	}
	while (t->next->next && t->next->next->type == WORD)
	{
		*cmd[y] = t->next->next->str;
		y++;
		t = t->next;
	}
	exec_push(&exec, *cmd, *filename, READ, env);
	j = 0;
	while(*filename[j])
	{
		*filename[j] = 0;
		j++;
	}
	y = 0;
}

static void	cmd_here(t_list_exec *exec, t_token *t,char ***cmd, char ***filename, int *x,t_env *env)
{
	j = 0;
	*filename[j++] = t->next->str;
	while(t->next->next && t->next->next->type == HEREDOC)
	{
		t = t->next->next;
		*filename[j] = t->next->str;
		j++;
	}
	while (t->next->next && t->next->next->type == WORD)
	{
		*cmd[y] = t->next->next->str;
		y++;
		t = t->next;
	}
	exec_push(&exec, *cmd, *filename, HEREDOC, env);
	j = 0;
	while(*filename[j])
	{
		*filename[j] = 0;
		j++;
	}
	y = 0;
}

t_exec	*add_exec(t_token *t, t_env *env)
{
	int		y;
	int j;
	int nb_filename = 0;
	int nb_cmd = 0;
	t_list_exec exec;

	char	**command;
	char	**filename;

	y = 0;
	exec_init(&exec);
	calcul_len_malloc(t, &nb_cmd, &nb_filename);
	printf("nb_filename: %d | nb_cmd: %d\n", nb_filename, nb_cmd);

	// filename = malloc(sizeof(char *) * nb_filename + 1);
	// command = malloc(sizeof(char *) * nb_cmd +1 );
	filename = malloc(10000);
	command = malloc(10000);

	while (t)
	{
		if (t->type == WORD)
			cmd_word(&exec, t, &command, &filename, &y, env);
		else if (t->type == WRITE)
		{
			cmd_write(&exec, t, &command, &filename, &j, env);
			t = t->next;
		}
		else if (t->type == APPEND)
		{
			cmd_apprent(&exec, t, &command, &filename, &j, env);
			y = 0;
			t = t->next;
		}
		else if (t->type == READ)
		{

			t = t->next;
		}
		else if (t->type == HEREDOC)
		{

			t = t->next;
		}
		t = t->next;
	}
	free(command);
	free(filename);
	return (exec.first);
}