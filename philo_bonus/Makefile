NAME = philo_bonus
HEADER = philo_bonus.h
SOURCES = main_bonus.c utils_bonus.c
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