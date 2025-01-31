/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ptr_to_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:59:23 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/12 10:38:07 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calculate_how_many_numbers(unsigned long number);

static char	*hex_to_str(unsigned long number);

int	convert_ptr_to_str(va_list args)
{
	unsigned long	number;
	char			*buffer;
	size_t			length;
	int				result;

	number = (unsigned long)va_arg(args, void *);
	if (number == 0)
		return (write(1, "(nil)", 5));
	buffer = hex_to_str(number);
	if (!buffer)
		return (0);
	length = ft_strlen(buffer);
	result = write(1, "0x", 2);
	result += write(1, buffer, length);
	free(buffer);
	return (result);
}

static char	*hex_to_str(unsigned long number)
{
	char	*buffer;
	char	*hex_digits;
	int		length;

	hex_digits = "0123456789abcdef";
	length = calculate_how_many_numbers(number);
	buffer = (char *)malloc(length + 1);
	if (!buffer)
		return (NULL);
	buffer[length] = '\0';
	while (length--)
	{
		buffer[length] = (hex_digits[number % 16]);
		number /= 16;
	}
	return (buffer);
}

static int	calculate_how_many_numbers(unsigned long number)
{
	int	length;

	length = 0;
	if (number == 0)
		length = 1;
	while (number)
	{
		number /= 16;
		length++;
	}
	return (length);
}
