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
	OPTION,
	PIPE,
	APPEND,
	WRITE,
	HEREDOC,
	READ
}			e_type;

typedef struct s_token
{
	char			*str;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

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
void	prompt(/*voir ce qu'il y a pas a passer*/);
int	parsing(char *line);
#endif
