/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:53:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/19 12:19:37 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		parse_format(const char *format, va_list args);
int		convert_hex_to_str(va_list args, char specifier);
int		print_char(va_list args);
int		print_str(va_list args);
int		handle_specifier(char specifier, va_list args);
int		convert_int_to_str(va_list args);
int		print_percentage(void);
int		convert_ptr_to_str(va_list args);
int		convert_unsigned_to_str(va_list args);
size_t	ft_strlen(const char *s);

#endif /* FT_PRINTF_H */
