/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:41:47 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/22 14:49:29 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "libft.h"

int	ft_abs(int n);

int	main(int argc, char **argv)
{
	int	result;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	result = ft_abs(ft_atoi(argv[1]));
	ft_printf("%d\n", result);
	return (0);
}*/

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
