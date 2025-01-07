/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:03:30 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/21 16:19:33 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	fizzbuzz(int argc, char **argv);

int	main(int argc, char **argv)
{
	fizzbuzz(argc, argv);
	return (0);
}*/

void	fizzbuzz(int argc, char **argv)
{
	int	number;
	int	limit;

	if (argc < 2)
		return ;
	number = 1;
	limit = ft_atoi(argv[1]);
	while (number <= limit)
	{
		if (number % 3 == 0 && number % 5 == 0)
			write(1, "fizzbuzz", 8);
		else if (number % 3 == 0)
			write(1, "fizz", 4);
		else if (number % 5 == 0)
			write(1, "buzz", 4);
		else
			ft_putnbr(number);
		write(1, "\n", 1);
		number++;
	}
}
