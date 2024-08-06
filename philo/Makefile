SOURCES = main.c utils.c actions.c
NAME = philo
CC = cc
CFLAGS= -Wall -Wextra -Werror

$(NAME): $(SOURCES) philo.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(NAME)

fclean:	clean

re: fclean all

.PHONY: all clean fclean re