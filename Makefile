##
## SYSTEM PROJECT, 2021
## makefile
## File description:
## file
##


SRC = src/testMono.cpp

CC =	g++

OBJ =	$(SRC:.c=.o)

NAME =		monoChr

CFLAGS = -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	rm -rf src/*.o
	rm -rf tests/*.o*

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY:	all clean fclean re