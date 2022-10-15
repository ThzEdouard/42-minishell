NAME	= minitest
FILE = src/parsing/prompteur.c src/parsing/list_token.c src/parsing/parsing.c src/minishell.c\
		src_utils/ft_strjoin.c src_utils/ft_strlen.c src_utils/ft_strdup.c src_utils/ft_strcpy.c src_utils/ft_strcmp.c src_utils/ft_strcat.c src_utils/ft_substr.c
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rfv

OBJ = $(FILE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lreadline

clean:
			$(RM) -rf $(OBJ)

fclean:		clean
			$(RM) -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re