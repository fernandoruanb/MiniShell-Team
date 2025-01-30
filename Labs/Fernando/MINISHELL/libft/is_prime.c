/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_prime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:12:42 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/21 16:25:38 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	is_prime(int n);

int	main(int argc, char **argv)
{
	int	number;
	int	result;

	if (argc < 2)
		return (1);
	number = ft_atoi(argv[1]);
	result = is_prime(number);
	ft_printf("O resultado é: %d\n", result);
	return (0);
}*/

int	is_prime(int n)
{
	int	attempt;

	if (n <= 1)
		return (0);
	attempt = 2;
	while (attempt * attempt <= n)
	{
		if (n % attempt == 0)
			return (0);
		attempt++;
	}
	return (1);
}
