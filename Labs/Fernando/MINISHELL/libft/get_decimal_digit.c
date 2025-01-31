/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_decimal_digit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:08:20 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/22 10:20:52 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	get_decimal_digit(char c, int str_base);

int	main(int argc, char **argv)
{
	int	result;

	if (argc < 3)
		return (1);
	result = get_decimal_digit(argv[1][0], ft_atoi(argv[2]));
	ft_printf("%d\n", result);
	return (0);
}*/

int	get_decimal_digit(char c, int str_base)
{
	int	max_digit;

	if (str_base < 2 || str_base > 16)
		return (-1);
	if (str_base <= 10)
		max_digit = str_base - 1 + '0';
	else
		max_digit = str_base - 10 - 1 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'z' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}
