
NAME = Philosophers

CC = cc 
CFLAGS = -I include/ -Wall -Werror -Wextra -g3  -pthread
SRC = 	pilosophers.c  utils.c pthread.c list.c forks.c general_init.c eating_routine.c checker.c
OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:

	rm -f $(OBJECTS)

fclean: clean 
	
	rm -f $(NAME)

re: fclean all
.PHONY: re clean fclean all