# Name of the program or the library

NAME = minishell

# Compilers and flags

CC = cc
CFLAGS = -Wall -Werror -Wextra
READLINEFLAGS = -lreadline

# Directories

SRCDIR = srcs
INCDIR = includes
LIBFT_DIR = libft

# LIBFT

LIBFT = libft/libft.a

# SRCS

SRCS =  $(SRCDIR)/minishell/minishell.c\
	$(SRCDIR)/execute/execute.c\
	$(SRCDIR)/builtins/ft_cd.c\
	$(SRCDIR)/builtins/ft_env.c\
	$(SRCDIR)/builtins/ft_echo.c\
	$(SRCDIR)/builtins/builtins.c\
	$(SRCDIR)/builtins/is_only_spaces.c\
	$(SRCDIR)/minishell/free_shell.c

# OBJS

OBJS = $(SRCS:%.c=%.o)

# Main

all: $(NAME)

# Main rule

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(LIBFT_DIR) -o $(NAME) $(OBJS) $(LIBFT) $(READLINEFLAGS)

# clean

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

# full clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

# restart

re: fclean all

.PHONY: fclean all clean re
