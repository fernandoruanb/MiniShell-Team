/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_power_of_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:43 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/19 15:21:34 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "libft.h"

int	is_power_of_2(unsigned int n);

int	main(int argc, char **argv)
{
	int	result;

	if (argc < 2)
		return (1);
	result = is_power_of_2(ft_atoi(argv[1]));
	ft_printf("%d\n", result);
	return (0);
}*/

int	is_power_of_2(unsigned int n)
{
	if (n == 0)
		return (0);
	return ((n & (n - 1)) == 0);
}
