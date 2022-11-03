/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:06:52 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/03 15:15:21 by eflaquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include "utils.h"

# define SUCCESS 0
# define FAIL 1

typedef enum s_type
{
	WORLD,
	PIPE,
	APPEND,
	WRITE,
	HEREDOC,
	READ
}			e_type;

typedef struct s_env
{
	char	*str;
	struct s_env *next;
}				t_env;

typedef struct s_token
{
	char			*str;
	e_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_path
{
	char	**paths;
	char	*path;
	char	*command_path;
}				t_path;

typedef struct s_file
{
	char	**filename;
	int		*file;
}				t_file;

typedef struct s_exec
{
	e_type	type;
	char	**cmd;
	char	*path_cmd;
	int		pipefd[2];
	pid_t	pid;
	t_path	*path;
	t_file	*file;
	struct s_exec *prev;
	struct s_exec *next;
}			t_exec;

typedef struct s_list_exec
{
	t_exec *first;
	t_exec *last;
}				t_list_exec;

typedef struct s_list_token
{
	t_token *first;
	t_token *last;
}				t_list_token;

/* *************************************************************************** */
/*------------------------------prompt in parsing------------------------------*/
/* *************************************************************************** */
void	token_init(t_list_token *l);
void	token_push(t_list_token *l, char *str);
void	token_clear(t_list_token *l);
void	prompt(t_env *env);
int		parsing(char *line);
void	add_token(t_token *t);
int		verification_token(t_token *t);
/* *************************************************************************** */
/*------------------------------env------------------------------*/
/* *************************************************************************** */
t_env	*new_elem(char *str);
void	generator_env(t_env **env, char **envp);
/* *************************************************************************** */
/*------------------------------exec------------------------------*/
/* *************************************************************************** */
//exec fonction sur l'autre ;)
void	exec_init(t_list_exec *l);
void	exec_push(t_list_exec *l, char **cmd, char **filename, t_env *env);
void	exec_clear();//clear a faire ;)
void	ft_free_paths(t_exec *exec);//les free a farie
/* *************************************************************************** */
/*------------------------------bulting------------------------------*/
/* *************************************************************************** */





#endif
