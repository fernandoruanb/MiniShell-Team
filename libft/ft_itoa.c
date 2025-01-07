/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:23:53 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/15 12:23:54 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

static int	calculate_how_many_numbers(int n);

/*char	*ft_itoa(int n);

int	main(int argc, char **argv)
{
	char	*result;

	if (argc < 2)
		return (1);
	result = ft_itoa(atoi(argv[1]));
	printf("(MY FUNCTION) %s.\n", result);
	return (0);
}*/

char	*ft_itoa(int n)
{
	char			*buffer;
	int				length;
	unsigned int	number;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		number = -n;
	else
		number = n;
	length = calculate_how_many_numbers(n);
	buffer = (char *)malloc(length + 1);
	if (!buffer)
		return (NULL);
	buffer[length] = '\0';
	while (length--)
	{
		buffer[length] = (number % 10) + '0';
		number /= 10;
	}
	if (n < 0)
		buffer[0] = '-';
	return (buffer);
}

static int	calculate_how_many_numbers(int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n)
	{
		n /= 10;
		length++;
	}
	return (length);
}
