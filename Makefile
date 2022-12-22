
NAME		= minishell
SRC_DIR		= ./
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -g #-Wall -Werror -Wextra -g
RM			= rm -f
SRC_MINISHEL	= src/
FT_MINISHELL = minishell signals

SRC_PARSING = src/parsing/
FT_PARSING = prompter list_token parsing add_token errors \
			verifications 

SRC_ENV = src/env/
FT_ENV = list_env

SRC_EXEC = src/exec/
FT_EXEC = list_exec add_exec childs exec heredoc exec_utils add_exec_cmd \
		exec_init exec_init_builtins files exec_malloc

SRC_BUILTINS = src/builtins/
FT_BUILTINS = ft_cd ft_echo ft_env ft_exit ft_export ft_pwd ft_unset

SRC_UTILS = src_utils/
FT_UTILS = ft_realloc ft_strjoin ft_strlen ft_strdup ft_strcpy ft_strcmp \
		 ft_strcat ft_substr ft_split ft_strnstr ft_putstr_fd ft_atoi ft_itoa \
		 get_next_line_utils get_next_line ft_realloc_2

SRC_FILES+=$(addprefix $(SRC_MINISHEL),$(FT_MINISHELL))
SRC_FILES+=$(addprefix $(SRC_PARSING),$(FT_PARSING))
SRC_FILES+=$(addprefix $(SRC_EXEC),$(FT_EXEC))
SRC_FILES+=$(addprefix $(SRC_ENV),$(FT_ENV))
SRC_FILES+=$(addprefix $(SRC_BUILTINS),$(FT_BUILTINS))
SRC_FILES+=$(addprefix $(SRC_UTILS),$(FT_UTILS))

SRC 		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

all:		$(NAME)
			@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "\033[0;32m [OK] \033" $<
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
			mkdir -p $(OBJ_DIR)
			mkdir -p $(OBJ_DIR)$(SRC_MINISHEL)
			mkdir -p $(OBJ_DIR)$(SRC_PARSING)
			mkdir -p $(OBJ_DIR)$(SRC_EXEC)
			mkdir -p $(OBJ_DIR)$(SRC_ENV)
			mkdir -p $(OBJ_DIR)$(SRC_BUILTINS)
			mkdir -p $(OBJ_DIR)$(SRC_UTILS)

clean:
			$(RM) -rf $(OBJ_DIR)

fclean:		clean
			$(RM) -f $(NAME)

re:		fclean all

val:	all
			valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=readline_leaks ./minishell

.PHONY:		all clean fclean re
