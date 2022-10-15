

#				//NAME AND COMPILATION\\ #
NAME		= minishell
SRC_DIR		= ./
OBJ_DIR		= obj/
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f
#					//SOUCES\\  #
SRC_MINISHEL	= src/
FT_MINISHELL = minishell

SRC_PARSING = src/parsing/
FT_PARSING = prompteur list_token parsing add_token

SRC_UTILS = src_utils/
FT_UTILS = ft_strjoin ft_strlen ft_strdup ft_strcpy ft_strcmp ft_strcat ft_substr


#				//ADD TO SRC_DIR\\#
SRC_FILES+=$(addprefix $(SRC_MINISHEL),$(FT_MINISHELL))
SRC_FILES+=$(addprefix $(SRC_PARSING),$(FT_PARSING))
SRC_FILES+=$(addprefix $(SRC_UTILS),$(FT_UTILS))

SRC 		= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

all:		$(NAME)
			@echo "\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@mkdir -p $(OBJ_DIR)$(SRC_MINISHEL)
			@mkdir -p $(OBJ_DIR)$(SRC_PARSING)
			@mkdir -p $(OBJ_DIR)$(SRC_UTILS)

clean:
			@$(RM) -rf $(OBJ_DIR)

fclean:		clean
			@$(RM) -f $(NAME)

re:		fclean all


.PHONY:		all clean fclean re


#NAME	= minitest
#FILE = src/parsing/prompteur.c src/parsing/list_token.c src/parsing/parsing.c  src/parsing/add_token.c src/minishell.c \
#		src_utils/ft_strjoin.c src_utils/ft_strlen.c src_utils/ft_strdup.c src_utils/ft_strcpy.c src_utils/ft_strcmp.c src_utils/ft_strcat.c src_utils/ft_substr.c
#CC = cc
#CFLAGS = -Wall -Wextra -Werror -g
#RM = rm -rfv
#
#OBJ = $(FILE:.c=.o)
#
#all: $(NAME)
#
#$(NAME): $(OBJ)
#			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline
#
#clean:
#			$(RM) -rf $(OBJ)
#
#fclean:		clean
#			$(RM) -f $(NAME)
#
#re:		fclean all
#
#.PHONY:		all clean fclean re