NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g  -pthread

SRC = 	main.c			\
		parsing.c		\
		parsing2.c		\
		init_and_destroy.c			\
		time_and_print.c		\
		routine_and_handler.c			\
		doing_things.c	\

OBJ = ${SRC:%.c=%.o}

all : philo.h ${NAME}

RM = rm -rf

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o $(NAME) ${OBJ}

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean
