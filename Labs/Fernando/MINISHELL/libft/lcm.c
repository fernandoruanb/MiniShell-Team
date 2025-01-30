/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:31:07 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/23 12:44:53 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	lcm(int a, int b);

int	main(int argc, char **argv)
{
	int	result;

	(void)argc;
	result = lcm(ft_atoi(argv[1]), ft_atoi(argv[2]));
	ft_printf("O MMC é: %d\n", result);
	return (0);
}*/

int	lcm(int a, int b)
{
	int	start;

	if (a > b)
		start = a;
	else
		start = b;
	while (1)
	{
		if (start % a == 0 && start % b == 0)
			break ;
		start++;
	}
	return (start);
}
