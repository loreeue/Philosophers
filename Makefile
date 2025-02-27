NAME = philo

SRC = actions.c death.c dinner.c handle.c\
	init.c main.c parsing.c safe_malloc.c\
	synchro.c utils.c values.c write.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN_PASTEL = \033[38;5;121m
BLUE_PASTEL = \033[38;5;110m
RESET = \033[0m

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN_PASTEL)Compilation complete! 🍏$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(BLUE_PASTEL)Clean complete! 🗑️$(RESET)"

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "$(BLUE_PASTEL)Full clean complete! 🗑️ 🗑️$(RESET)"

all: $(NAME)

re: fclean all

.PHONY: clean fclean all re
