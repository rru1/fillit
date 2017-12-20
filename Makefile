NAME = fillit
SRC = *.c
OBJ = *.o
CC = gcc
CFLAGS	:= -Wall -Wextra -Werror -pedantic -std=c99

all:

$(NAME):
	$(CC) $(CFLAGS) $(SRC) $(NAME)
clean:
	rm $(NAME)
fclean:

re: fclean all
