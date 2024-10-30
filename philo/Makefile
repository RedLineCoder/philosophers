NAME = philo
HEADER = philo.h
SOURCES = main.c utils.c actions.c
CC = cc
CFLAGS= -Wall -Wextra -Werror

$(NAME): $(SOURCES) $(HEADER)
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(NAME)

fclean:	clean

re: fclean all

.PHONY: all clean fclean re