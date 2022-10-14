NAME	= minitest
FILE = src/parsing/prompteur.c src/minishell.c
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