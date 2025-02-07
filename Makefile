
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
		syntax_check/init_utils.c\
		syntax_check/clean_program.c\
		syntax_check/check_syntax.c\
		syntax_check/get_command.c\
		syntax_check/final_case.c\
		syntax_check/check_invalid_brackets_position.c\
		syntax_check/case_arg.c\
		syntax_check/case_limiter.c\
		syntax_check/case_command.c\
		syntax_check/is_insider_quotes.c\
		syntax_check/test_all_paths.c\
		syntax_check/is_absolute_path_quotes.c\
		syntax_check/case_builtins_quotes.c\
		syntax_check/is_environment.c\
		syntax_check/case_builtins.c\
		syntax_check/extra_cases.c\
		syntax_check/check_brackets.c\
		syntax_check/check_invalid_things.c\
		syntax_check/case_fd.c\
		syntax_check/check_is_directory.c\
		syntax_check/check_is_valid_fd.c\
		syntax_check/is_number.c\
		syntax_check/case_redirect.c\
		syntax_check/extra_redirect_cases.c\
		syntax_check/heredoc_or_append.c\
		syntax_check/case_pipe.c\
		syntax_check/decrement_status.c\
		syntax_check/show_error_fd.c\
		syntax_check/free_each_split.c\
		syntax_check/exist_command.c\
		syntax_check/check_absolute_path.c\
		syntax_check/get_full_path.c\
		syntax_check/get_paths.c\
		syntax_check/show_paths.c\
		syntax_check/free_strs_flag.c\
		syntax_check/show_tokens.c\
		syntax_check/get_token.c\
		syntax_check/free_tokens.c\
		syntax_check/add_token.c\
		syntax_check/create_token.c\
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
