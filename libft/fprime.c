/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:06:50 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/24 17:26:30 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	fprime(int number);

int	main(int argc, char **argv)
{
	int	number;

	if (argc < 2 || argc > 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	number = ft_atoi(argv[1]);
	fprime(number);
	return (0);
}*/

void	fprime(int number)
{
	int	index;

	if (number == 1)
		ft_printf("1");
	index = 1;
	while (number >= ++index)
	{
		if (number % index == 0)
		{
			ft_printf("%d", index);
			if (number == index)
				break ;
			ft_printf("*");
			number /= index;
			index = 1;
		}
	}
	ft_printf("\n");
}
