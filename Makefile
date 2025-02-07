
NAME = minishell

SRC_DIR = src
SRCS = main/2-events.c \
		main/3-init.c \
		prompt/1-display_prompt.c \
		0-utils.c \
		prompt/2-exec_cmd.c \
		built_in/1-cd.c \
		built_in/5-echo.c \
		built_in/5.1-echo_utils.c \
		built_in/2-exit.c \
		lexer/1-lexer.c \
		lexer/2-handles.c \
		lexer/3-handle_quotes.c \
		lexer/4-handle_word.c \
		lexer/5-handle_pipe.c \
		1-token.c
	
SRC = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJ = $(SRC:.c=.o)
HEADER = include
LIBFT = libft
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I$(HEADER) -g

.DEFAULT_GOAL := all


intro:
	@echo "\033[1;32m===========================================\033[0m"
	@echo "\033[1;32m		$(NAME)								\033[0m"
	@echo "\033[1;32m===========================================\033[0m"

all: intro $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[1;33mCompiling	->	$<\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT)/libft.a:
	@make -C $(LIBFT)

#Creates libft.a. Copy to the current directory. Add libft.a to libprintf.a
$(NAME): $(OBJ) $(LIBFT)/libft.a
	@$(CC) $(CFLAGS) $(SRC_DIR)/main/1-main.c $(OBJ) $(LIBFT)/libft.a -o $(NAME) -lreadline -lncurses

leak: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 2>&1 | \
	grep -i "no leaks are possible" > /dev/null && echo "Tudo nos conformes." || echo "Faz denovo, faz direito!!"

clean:
	@echo "\033[1;32m===========================================\033[0m"
	@echo "\033[1;32m		OBJECTS REMOVED						\033[0m"
	@echo "\033[1;32m===========================================\033[0m"
	@rm -f $(OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@echo "\033[1;32m===========================================\033[0m"
	@echo "\033[1;32m		$(NAME) REMOVED						\033[0m"
	@echo "\033[1;32m===========================================\033[0m"
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
