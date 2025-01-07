/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:01:12 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/13 14:46:40 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		printed_char;

	if (!format)
		return (-1);
	printed_char = 0;
	va_start(args, format);
	printed_char += parse_format(format, args);
	va_end(args);
	return (printed_char);
}
