CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

CFILES = philo.c \
	 philo_utils.c \
	 philo_utils2.c \
	 philo_forks.c \

OBJECTS=$(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o  $@
clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)
re: fclean all
