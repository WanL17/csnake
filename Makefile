CC      = gcc

CFLAGS 	= -Iinclude

LDFLAGS = -lncurses

NAME    = csnake

SRC    	= src/main.c \
		  src/game.c \
		  src/exit.c \
		  src/move_snake.c \
		  src/delete.c

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY : all clean fclean re
