# Name of the program or library

NAME = libft.a

# Compilers and flags

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(HEADER) -g

# Header
HEADER = ../include

# Directories

SRCDIR = .
INCDIR = .

# Archives .c

SRCS =  $(SRCDIR)/ft_isalpha.c\
	$(SRCDIR)/free_splits.c\
	$(SRCDIR)/ft_isdigit.c\
	$(SRCDIR)/ft_isalnum.c\
	$(SRCDIR)/ft_isprint.c\
	$(SRCDIR)/ft_isascii.c\
	$(SRCDIR)/ft_strlen.c\
	$(SRCDIR)/ft_memset.c\
	$(SRCDIR)/ft_bzero.c\
	$(SRCDIR)/ft_strchr.c\
	$(SRCDIR)/ft_strrchr.c\
	$(SRCDIR)/ft_toupper.c\
	$(SRCDIR)/ft_tolower.c\
	$(SRCDIR)/ft_strncmp.c\
	$(SRCDIR)/ft_memchr.c\
	$(SRCDIR)/ft_atoi.c\
	$(SRCDIR)/ft_memcmp.c\
	$(SRCDIR)/ft_strlcpy.c\
	$(SRCDIR)/ft_strnstr.c\
	$(SRCDIR)/ft_strdup.c\
	$(SRCDIR)/ft_putchar_fd.c\
	$(SRCDIR)/ft_putstr_fd.c\
	$(SRCDIR)/ft_putendl_fd.c\
	$(SRCDIR)/ft_putnbr_fd.c\
	$(SRCDIR)/ft_calloc.c\
	$(SRCDIR)/ft_itoa.c\
	$(SRCDIR)/ft_memmove.c\
	$(SRCDIR)/ft_strlcat.c\
	$(SRCDIR)/ft_memcpy.c\
	$(SRCDIR)/ft_striteri.c\
	$(SRCDIR)/ft_strmapi.c\
	$(SRCDIR)/ft_strjoin.c\
	$(SRCDIR)/ft_substr.c\
	$(SRCDIR)/ft_strtrim.c\
	$(SRCDIR)/ft_split.c\
	$(SRCDIR)/get_next_line.c\
	$(SRCDIR)/ft_printf.c\
	$(SRCDIR)/parse_format.c\
	$(SRCDIR)/convert_hex_to_str.c\
	$(SRCDIR)/print_char.c\
	$(SRCDIR)/print_str.c\
	$(SRCDIR)/handle_specifier.c\
	$(SRCDIR)/convert_int_to_str.c\
	$(SRCDIR)/print_percentage.c\
	$(SRCDIR)/convert_ptr_to_str.c\
	$(SRCDIR)/convert_unsigned_to_str.c\
	$(SRCDIR)/rev_print.c\
	$(SRCDIR)/first_word.c\
	$(SRCDIR)/fizzbuzz.c\
	$(SRCDIR)/ft_putstr.c\
	$(SRCDIR)/ft_strcpy.c\
	$(SRCDIR)/ultimate_ft_strlen.c\
	$(SRCDIR)/ft_swap.c\
	$(SRCDIR)/repeat_alpha.c\
	$(SRCDIR)/rot_13.c\
	$(SRCDIR)/rotone.c\
	$(SRCDIR)/search_and_replace.c\
	$(SRCDIR)/ulstr.c\
	$(SRCDIR)/alpha_mirror.c\
	$(SRCDIR)/camel_to_snake.c\
	$(SRCDIR)/do_op.c\
	$(SRCDIR)/ulstr_v2.c\
	$(SRCDIR)/ft_strcspn.c\
	$(SRCDIR)/ft_strpbrk.c\
	$(SRCDIR)/ft_strrev.c\
	$(SRCDIR)/ft_strspn.c\
	$(SRCDIR)/inter.c\
	$(SRCDIR)/is_power_of_2.c\
	$(SRCDIR)/last_word.c\
	$(SRCDIR)/max.c\
	$(SRCDIR)/print_bits.c\
	$(SRCDIR)/reverse_bits.c\
	$(SRCDIR)/snake_to_camel.c\
	$(SRCDIR)/swap_bits.c\
	$(SRCDIR)/union.c\
	$(SRCDIR)/wdmatch.c\
	$(SRCDIR)/ft_putnbr.c\
	$(SRCDIR)/is_prime.c\
	$(SRCDIR)/add_prime_num.c\
	$(SRCDIR)/epur_str.c\
	$(SRCDIR)/expand_str.c\
	$(SRCDIR)/get_decimal_digit.c\
	$(SRCDIR)/to_lower.c\
	$(SRCDIR)/ft_atoi_base.c\
	$(SRCDIR)/ft_abs.c\
	$(SRCDIR)/ft_range.c\
	$(SRCDIR)/ft_rrange.c\
	$(SRCDIR)/hidenp.c\
	$(SRCDIR)/lcm.c\
	$(SRCDIR)/paramsum.c\
	$(SRCDIR)/pgcd.c\
	$(SRCDIR)/print_hex.c\
	$(SRCDIR)/int_ft_strlen.c\
	$(SRCDIR)/rev_wstr.c\
	$(SRCDIR)/rostring.c\
	$(SRCDIR)/sort_int_tab.c\
	$(SRCDIR)/fprime.c\
	$(SRCDIR)/tab_mult.c\
	$(SRCDIR)/str_capitalizer.c\
	$(SRCDIR)/get_next_line_utils.c\
	$(SRCDIR)/ft_strcmp.c\
	$(SRCDIR)/ft_double_free.c\
	$(SRCDIR)/ft_atoi_but_better.c

# BONUS SRCS

BONUS_SRCS = 	$(SRCDIR)/ft_lstnew_bonus.c\
		$(SRCDIR)/ft_lstadd_front_bonus.c\
		$(SRCDIR)/ft_lstsize_bonus.c\
		$(SRCDIR)/ft_lstlast_bonus.c\
		$(SRCDIR)/ft_lstadd_back_bonus.c\
		$(SRCDIR)/ft_lstdelone_bonus.c\
		$(SRCDIR)/ft_lstclear_bonus.c\
		$(SRCDIR)/ft_lstiter_bonus.c\
		$(SRCDIR)/ft_lstmap_bonus.c\
		$(SRCDIR)/ft_list_size.c\
		$(SRCDIR)/ft_list_foreach.c\
		$(SRCDIR)/ft_list_remove_if.c

# Archives .o

OBJS = $(SRCS:$(SRCDIR)/%.c=%.o)
BONUS_OBJS = $(BONUS_SRCS:$(SRCDIR)/%.c=%.o)

# Check bonus relink

ifeq ($(findstring bonus,$(MAKECMDGOALS)),bonus)
	OBJS += $(BONUS_OBJS)
endif

.DEFAULT_GOAL := all

intro:
	@echo "\033[1;32m===========================================\033[0m"
	@echo "\033[1;32m		$(NAME) READY						\033[0m"
	@echo "\033[1;32m===========================================\033[0m"

# Main

all: intro $(NAME)

# Main rule

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	$(call title)

# Main bonus

bonus: $(NAME)

# .c -> .o

%.o: %.c
	@echo "\033[1;36mCompiling	->	$<\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clear archives

clean:
	@echo "\033[1;32m===========================================\033[0m"
	@echo "\033[1;32m		OBJECTS REMOVED						\033[0m"
	@echo "\033[1;32m===========================================\033[0m"
	@rm -f $(OBJS) $(BONUS_OBJS)

# Full clean

fclean: clean
	@echo "\033[1;32m===========================================\033[0m"
	@echo "\033[1;32m		$(NAME) REMOVED						\033[0m"
	@echo "\033[1;32m===========================================\033[0m"
	@rm -f $(NAME)

# Restart

re: fclean $(NAME)

.PHONY: all clean fclean re bonus

