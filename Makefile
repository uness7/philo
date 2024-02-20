CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread

NAME = philo

CFILES = philo.c \
	 init_philo.c \
	 philo_utils.c \
	 routine.c \
	 routine_utils.c \
	 run_simulation.c \
	 run_simulation_utils.c \
	 end_simulation.c \

OBJECTS=$(CFILES:.c=.o)

DISPLAYED_BANNER = 0

all: banner $(NAME)

banner:
ifeq ($(DISPLAYED_BANNER), 0)
	@echo "888      .d88888b.        d8888 8888888b. 8888888 888b    888  .d8888b."
	@echo "888     d88P   Y88b      d88888 888   Y88b  888   8888b   888 d88P  Y88b"
	@echo "888     888     888     d88P888 888    888  888   88888b  888 888    888"
	@echo "888     888     888    d88P 888 888    888  888   888Y88b 888 888"
	@echo "888     888     888   d88P  888 888    888  888   888 Y88b888 888  88888"
	@echo "888     888     888  d88P   888 888    888  888   888  Y88888 888    888"
	@echo "888     Y88b. .d88P d8888888888 888  .d88P  888   888   Y8888 Y88b  d88P"
	@echo "88888888  Y88888P  d88P     888 8888888P  8888888 888    Y888  Y8888P88"
	@echo "\n"
	$(eval DISPLAYED_BANNER = 1)
endif

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)
	$(eval DISPLAYED_BANNER = 0)

re: fclean all
