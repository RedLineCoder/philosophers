SOURCES = main.c utils.c
NAME = philo
CC = cc
CFLAGS= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SOURCES) philo.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)

clean:
	$(RM) $(NAME)

fclean:	clean

re: fclean all

.PHONY: all clean fclean re