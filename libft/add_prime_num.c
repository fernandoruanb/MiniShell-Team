/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:26:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/21 16:37:17 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	add_prime_number(int argc, char **argv);

int	main(int argc, char **argv)
{
	add_prime_number(argc, argv);
	return (0);
}*/

void	add_prime_number(int argc, char **argv)
{
	int	total;
	int	num;

	if (argc < 2)
	{
		write(1, "0\n", 2);
		return ;
	}
	num = ft_atoi(argv[1]);
	if (num <= 0)
	{
		write(1, "0\n", 2);
		return ;
	}
	total = 0;
	while (num > 0)
	{
		if (is_prime(num))
			total += num;
		num--;
	}
	ft_putnbr(total);
	write(1, "\n", 1);
}
