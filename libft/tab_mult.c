/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:48:32 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/28 08:56:58 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	tab_mult(int number);

int	main(int argc, char **argv)
{
	int	index;
	int	result;
	int	number;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	number = ft_atoi(argv[1]);
	tab_mult(number);
	return (0);
}*/

void	tab_mult(int number)
{
	int	result;
	int	index;

	index = 1;
	while (index < 10)
	{
		result = number * index;
		ft_putnbr(index);
		write(1, " x ", 3);
		ft_putnbr(number);
		write(1, " = ", 3);
		ft_putnbr(result);
		write(1, "\n", 1);
		index++;
	}
}
