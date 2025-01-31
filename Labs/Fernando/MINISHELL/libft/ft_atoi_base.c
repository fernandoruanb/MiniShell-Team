/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:52:16 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/22 11:24:53 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	ft_atoi_base(const char *str, int str_base);

int	main(int argc, char **argv)
{
	int	result;

	if (argc < 2)
		return (1);
	result = ft_atoi_base(argv[1], ft_atoi(argv[2]));
	ft_printf("%d\n", result);
	return (0);
}*/

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	signal;
	int	digit;

	result = 0;
	signal = 1;
	digit = 0;
	if (!str || str_base < 2 || str_base > 16)
		return (-1);
	if (*str == '-')
	{
		signal *= -1;
		str++;
	}
	while (*str)
	{
		digit = get_decimal_digit(*str, str_base);
		if (digit == -1)
			return (-1);
		result = result * str_base + digit;
		str++;
	}
	return (result * signal);
}
