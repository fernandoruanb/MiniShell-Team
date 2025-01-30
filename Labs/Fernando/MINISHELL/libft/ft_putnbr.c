/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:54:37 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/21 16:11:27 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	ft_putnbr(int n);

int	main(int argc, char **argv)
{
	int	number;

	if (argc < 2)
		return (1);
	number = ft_atoi(argv[1]);
	ft_putnbr(number);
	write(1, "\n", 1);
	return (0);
}*/

void	ft_putnbr(int n)
{
	long	number;
	char	digit;

	number = n;
	if (n < 0)
	{
		write(1, "-", 1);
		number = -number;
	}
	if (number >= 10)
		ft_putnbr(number / 10);
	digit = (number % 10) + '0';
	write(1, &digit, 1);
}
