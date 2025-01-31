/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:25:27 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/23 14:26:12 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	pgcd(int nbr1, int nbr2);

int	main(int argc, char **argv)
{
	int	nbr1;
	int	nbr2;
	int	result;

	if (argc == 3)
	{
		nbr1 = ft_atoi(argv[1]);
		nbr2 = ft_atoi(argv[2]);
		if (nbr1 > 0 && nbr2 > 0)
		{
			result = pgcd(nbr1, nbr2);
			ft_printf("MDC: %d\n", result);
		}
		else
			return (1);
	}
	return (0);
}*/

int	pgcd(int nbr1, int nbr2)
{
	while (nbr1 != nbr2)
	{
		if (nbr1 > nbr2)
			nbr1 -= nbr2;
		else
			nbr2 -= nbr1;
	}
	return (nbr1);
}
