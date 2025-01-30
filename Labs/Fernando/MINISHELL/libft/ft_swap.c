/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:06:52 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/17 11:14:40 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	ft_swap(int *a, int *b);

int	main(int argc, char **argv)
{
	int	a;
	int	b;

	if (argc < 3)
		return (1);
	a = ft_atoi(argv[1]);
	b = ft_atoi(argv[2]);
	ft_printf("Os números passados foram: %d e %d\n", a, b);
	ft_swap(&a, &b);
	ft_printf("Os números ficaram: %d e %d\n", a, b);
	return (0);
}*/

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
