/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eflaquet <eflaquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:06:52 by eflaquet          #+#    #+#             */
/*   Updated: 2022/11/07 23:06:25 by eflaquet         ###   ########.fr       */
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
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "utils.h"

# define SUCCESS 0
# define FAIL 1

# define ECHO_CODE "$?"

# define NAME_SHELL "doudou"
# define NAME_SHELL_ERROR "\e[1;91mDoudou\e[0m"
# define ERROR_0 "\e[1;90m%s: syntax error near unexepted token %s\n\e[0m"
# define ERROR_3 "\e[1;90m%s: syntax error near unexpected token `newline'\n\e[0m"
# define ERROR_1 "\e[1;90m%s : %s: Is a directory\n\e[0m"
# define ERROR_2 "\e[1;90m%s : %s: command not found\n\e[0m"
# define ERROR_5 "\e[1;90m%s : %s: %s: Not a directory\n\e[0m"

typedef enum s_type
{
	WORD,
	PIPE,
	APPEND,
	WRITE,
	HEREDOC,
	READ
}			t_type;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_exec
{
	char			**cmd;
	char			*path_cmd;
	int				pipefd[2];
	pid_t			pid;
	char			**paths;
	char			*path;
	char			*command_path;
	char			**filename;
	int				*file;
	t_type			type;
	struct s_exec	*prev;
	struct s_exec	*next;
}			t_exec;

typedef struct s_list_exec
{
	t_exec	*first;
	t_exec	*last;
}				t_list_exec;

typedef struct s_list_token
{
	t_token	*first;
	t_token	*last;
}				t_list_token;

typedef struct s_add
{
	int		i;
	int		y;
	int		j;
	char	**command;
	char	**filename;
}				t_add;

/* **************************************************************** */
/*------------------------------prompt in parsing-------------------*/
/* ***************************************************************** */
void	token_init(t_list_token *l);
void	token_push(t_list_token *l, char *str);
void	token_clear(t_list_token *l);
void	prompt(t_env **env, char **envp);
int		parsing(char *line, t_list_token *t);
void	add_token(t_token *t);
int		verification_token(t_token *t);
void	ft_quite_error(char s, int len);
void	ft_code_error(t_type type, char *str, int len);
int		expand_utils(t_list_token *l, t_env *env);
void	expand_process(t_token *tmp, int *tmp1, int *i);
int		update_str(char **str, t_env *env, int i, int len);
/* ************************************************************** */
/*------------------------------env------------------------------*/
/* ************************************************************ */
t_env	*new_elem(char *str);
void	generator_env(t_env **env, char **envp);
char	*get_name(t_env *env, char *s, int len);
void	clear_env(t_env **env);
//faire aussi tous les chngement qui'il y a avec les bulting
/* *************************************************************** */
/*------------------------------exec------------------------------*/
/* ************************************************************* */
//exec fonction sur l'autre ;)
void	exec_init(t_list_exec *l);
void	exec_push(t_list_exec *l, char **cmd, char **filename, t_type type);
void	exec_clear(t_list_exec *l);
t_exec	*add_exec(t_token *t, t_env *env);
void	ft_free_paths(t_exec *exec);
t_exec	*set_path(t_exec *e, t_env *env);

void	ft_error(char *error);
void	ft_free_all(char **tab);
int		ft_open_files(t_exec *data, int i);
void	ft_childs(t_exec *data, char **envp, t_env **env);
void	ft_exec(t_exec *pipe, char **envp, t_env **env);
int		ft_mode(t_exec *data);
void	ft_here_doc(t_exec *data, int i);
void	ft_free_paths(t_exec *data);
void	ft_exec_init(t_exec *data, t_env **env);
void	ft_message(char *error);

int		ft_exec_builtins(t_exec *data, t_env **env);
int		ft_check_builtins(t_exec *data);
int		ft_check_heredoc(t_exec *data);

int		malloc_cmd_filename(t_token *t, t_add *values);
void	calcul_len_malloc(t_token *tmp, int *len_cmd, int *len_file);
void	cmd_word(t_list_exec *exec, t_token *t, t_add *values, t_env *env);
t_token	*cmd_write(t_list_exec *exec, t_token *t, t_add *values, t_env *env);
t_token	*cmd_append(t_list_exec *exec, t_token *t, t_add *values, t_env *env);
t_token	*cmd_read(t_list_exec *exec, t_token *t, t_add *values, t_env *env);
t_token	*cmd_here(t_list_exec *exec, t_token *t, t_add *values, t_env *env);

/* **************************************************************** */
/*------------------------------bulting------------------------------*/
/* ***************************************************************** */

int		ft_pwd(void);
void	ft_exit(char **cmd);
int		ft_env(t_env *env);
void	ft_export(t_env **env, char *cmd);
void	ft_unset(t_env **env, char *cmd);
int		ft_cd(t_env **env, char *cmd);
int		ft_echo(char **cmd);

void	expand(t_list_token *l, t_env *env);
int		add_list(t_list_token *l, char *line, int end);

#endif
