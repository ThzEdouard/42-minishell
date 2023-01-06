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
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "get_next_line.h"

# define SUCCESS 0
# define FAIL 1

# define ECHO_CODE "?"

# define NAME_SHELL "Minishell"
# define NAME_SHELL_ERROR "\e[1;91mMinishell\e[0m"
# define ERROR_0 "\e[1;90m%s: syntax error near unexpected token \n\e[0m"
# define ERROR_3 "\e[1;90m%s: syntax error near unexpected token `newline'\n\e[0m"
# define ERROR_1 "\e[1;90mMinishell\e : Is a directory\n\e[0m"
# define ERROR_2 "\e[1;90mMinishell\e : command not found\n\e[0m"
# define ERROR_5 "\e[1;90m%s : %s: %s: Not a directory\n\e[0m"

extern int	g_statesssss;

typedef enum s_type
{
	NOTHING,
	WORD,
	PIPE,
	APPEND,
	WRITE,
	HEREDOC,
	READ,
	COUNT
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

typedef struct s_files
{
	int				file;
	t_type			type;
	struct s_files	*prev;
	struct s_files	*next;
}					t_files;

typedef struct s_exec
{
	int				saveout;
	int				savein;
	char			**cmd;
	char			*path_cmd;
	int				pipefd[2];
	pid_t			pid;
	char			**paths;
	char			*path;
	char			*command_path;
	char			**filename;
	int				*file;
	int				fileproblem;
	t_type			*type;
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
	t_type	*type;
}				t_add;

/*list_env*/
t_env	*new_elem(char *str);
char	*create_code(void);
char	*get_name(t_env *env, char *s, int len);
void	generator_env(t_env **env, char **envp);
void	clear_env(t_env **env);

/*add_exec_cmd*/
void	cmd_word(t_list_exec *exec, t_token *t, t_add *values, t_env *env);
t_token	*write_append(t_list_exec *exec, t_token *t, t_add *values, t_env *env);
t_token	*read_heredoc(t_list_exec *exec, t_token *t, t_add *values, t_env *env);
void	read_heredoc_2(t_list_exec *exec, t_add *values, t_env *env);

/*add_exec*/
t_exec	*add_exec(t_token *t, t_env *env);
void	free_add_exec(t_add values);

/*childs*/
void	ft_childs(t_exec *data, char **envp, t_env **env);
int		ft_exec_builtins(t_exec *data, t_env **env);
int		ft_check_builtins(t_exec *data);
int		ft_check_redirs(t_exec *data);

/*exec_init_builtins*/
void	ft_exec_builtins_init(t_exec *data, t_env **env);
void	ft_exec_builtins_init_2(t_exec *data, int i);

/*exec_init*/
void	ft_exec_init(t_exec *data, t_env **env);
void	ft_exec_init_2(t_exec *data, int i);
void	ft_exec_init_3(t_exec *data, t_env **env, int y, struct stat *stats);
void	add_exec_init(t_list_exec *l, t_add *values);
void	exec_init(t_list_exec *l);

/*exec_malloc*/
void	calcul_len_malloc(t_token *tmp, int *len_cmd, int *len_file);
int		malloc_cmd_filename(t_token *t, t_add *values);
int		malloc_command(t_add *values, int nb_cmd);
void	malloc_type(t_add *values);

/*exec_utils*/
void	ft_free_all(char **tab);
void	exec_push_v2(t_list_exec *l, char **cmd, char **filename, t_type *type);
void	exec_push_v2_2(t_exec *new, char **cmd, char **filename, t_type *type);
void	exec_clear(t_list_exec *l);
void	exec_clear_reset(t_list_exec *l);
void	tmp_clear(t_exec *tmp);

/*exec*/
int		ft_mode(t_exec *data);
void	ft_mode_heredoc(t_exec *tmp, int i, int *filenumber);
void	ft_exec(t_exec *p, char **envp, t_env **env);
void	ft_exec_process(t_exec *tmp, t_exec *p, char **envp, t_env **env);
void	ft_exec_process_builtins(t_exec *tmp, t_exec *p, t_env **env);

/*files*/
int		ft_open_files(t_exec *data, int i, int *filenumber);
int		ft_open_file_3(t_exec *tmp, int i);
int		ft_open_files_2(t_exec *tmp, int i, int *filenumber);
void	ft_close_files(t_exec *data);

/*heredoc*/
void	ft_heredoc(t_exec *data, int i, int *filenumber);
void	ft_heredoc_2(char *line, int temp);
void	ft_heredoc_3(t_exec *data, char *line, char *tmpfilename, int i);
int		ft_check_heredoc(t_exec *data);
void	ft_unlink_heredoc(t_exec *tmp);

/*list_exec*/
void	ft_free_paths(t_exec *data);
char	*ft_access(t_exec *exec);
char	*ft_path(t_exec *exec, t_env *env);
t_exec	*set_path(t_exec *t, t_env *env);

/*add_token*/
int		verification_arg(t_token *t);
int		verification_token(t_token *t);
void	add_token(t_token *t);
void	extand(t_token *t);
void	expand(t_token *t, t_env *env);
/*errors*/
void	ft_quit_error(char s, int len);
void	ft_code_error(t_type type, char *str, int len);
void	ft_error(char *error);
void	ft_message(char *error, t_exec *data, t_env **env, int code);

int	parsing(char *line, t_list_token *t, t_env *env);
void	token_init(t_list_token *l);
int		token_push(t_list_token *l, char *str);
void	View(t_list_token l);
void	token_clear(t_list_token *l);
int		add_list(t_list_token *l, char *line, int end);

/*prompter*/
char	*line_prompter(t_env **env, char **envp, t_list_token t, t_list_exec e);
void	prompter(t_env **env, char **envp);

/*verifications*/
int		verification_quote_2(int *start, char *line);
int		verif_up(char **lines);
int		up_code(char *line);
int		verification_quote(char *line);
int		ft_space(char c);

/*minishell*/
void	init_sig(void);
int		main(int argc, char **argv, char **envp);

/*signals*/
void	sig_int(int sig, siginfo_t *info, void *tmp);

/*realloc*/
int		ft_double_len_int(t_type *src);
int		*ft_realloc_int(char **src);
char	**ft_double_realloc(char **src);
char	**ft_double_realloc_2(char **src, char **malloc_src);
t_type	*ft_double_realloc_enum(t_type *src);
int		ft_double_len(char **src);

/*builtins*/
int		ft_cd(t_env **env, char *cmd);
int		checking_args(char **cmd, int *t, int i);
void	check_quit(char **cmd);
int		ft_echo(char **cmd);
int		ft_env(t_env *env);
void	exec_clears(t_exec *l);
void	ft_free_exit(t_exec *data, t_env **env, int code);
void	ft_exit_util(t_exec *data, t_env **env, char **cmd);
void	ft_exit(t_exec *data, t_env **env, char **cmd);
void	print_solo(t_env *env);
void	add_export(t_env **env, char *cmd, int ok, char *test);
void	check_export(t_env **env, char *cmd);
int		ft_export(t_env **env, char **cmd);
int		ft_pwd(void);
void	ft_delete_node(t_env *env);
int		ft_delete(t_env *tmp, char *tmp_str);
void	ft_unset(t_env **env, char *cmd);

#endif
