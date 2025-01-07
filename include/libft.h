/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:41:02 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/06 17:39:50 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;

}			t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_atoi(const char *nptr);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_itoa(int n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char *c));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
t_list		*ft_lstnew(void *content);
char		**ft_split(char const *s, char c);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char		*get_next_line(int fd, int flag);
int			ft_printf(const char *format, ...);
int			parse_format(const char *format, va_list args);
int			convert_hex_to_str(va_list args, char specifier);
int			print_char(va_list args);
int			print_str(va_list args);
int			handle_specifier(char specifier, va_list args, int total);
int			convert_int_to_str(va_list args);
int			print_percentage(void);
int			convert_ptr_to_str(va_list args);
int			convert_unsigned_to_str(va_list args);
char		*rev_print(char *str);
void		first_word(int argc, char **argv);
void		fizzbuzz(int argc, char **argv);
void		ft_putstr(char *str);
char		*ft_strcpy(char *s1, char *s2);
size_t		ultimate_ft_strlen(const char *s1, const char *s2, const char *s3);
void		ft_swap(int *a, int *b);
void		repeat_alpha(const char *str);
void		rot_13(char letter);
void		rotone(char letter);
void		search_and_replace(char *c, const char search, const char replace);
void		ulstr(char *str);
void		alpha_mirror(char *c);
void		camel_to_snake(char *str);
int			do_op(const char *n1, const char operator, const char *n2);
void		ulstr_v2(char *str);
size_t		ft_strcspn(const char *s, const char *reject);
char		*ft_strpbrk(const char *s1, const char *s2);
char		*ft_strrev(char *str);
size_t		ft_strspn(const char *s, const char *accept);
void		inter(const char *s1, const char *s2);
int			is_power_of_2(unsigned int n);
void		last_word(const char *s);
int			max(int *tab, unsigned int len);
void		print_bits(unsigned char octet);
char		reverse_bits(char octet);
void		snake_to_camel(char *s);
char		swap_bits(char octet);
void		union_display(const char *s1, const char *s2);
void		wdmatch(const char *s1, const char *s2);
void		ft_putnbr(int n);
int			is_prime(int n);
void		add_prime_num(int argc, char **argv);
void		epur_str(const char *str);
void		expand_str(const char *str);
int			get_decimal_digit(char c, int str_base);
char		to_lower(const char c);
int			ft_atoi_base(const char *str, int str_base);
int			ft_list_size(t_list *begin_list);
int			ft_abs(int n);
int			*ft_range(int start, int end);
int			*ft_rrange(int start, int end);
void		hidenp(const char *s1, const char *s2);
int			lcm(int a, int b);
int			paramsum(int argc);
int			pgcd(int nbr1, int nbr2);
void		print_hex(int n);
void		ft_list_foreach(t_list begin_list, void (*f)(void *));
void		ft_list_remove_if(t_list **begin_list, char data_ref, int (*cmp)());
int			int_ft_strlen(const char *s);
void		rev_wstr(const char *str);
void		rostring(const char *str, int index);
int			*sort_int_tab(int *tab, unsigned int size);
void		fprime(int number);
void		tab_mult(int number);
void		str_capitalizer(char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_double_free(void *a, void *b);

#endif /* LIBFT_H */
