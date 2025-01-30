/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:04:10 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/13 11:04:12 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>*/

static void	count_signal(char c, int *signal, int *count);

/*int	ft_atoi(const char *nptr);

int	main(int argc, char **argv)
{
	int	result;
	int	result2;

	if (argc < 2)
		return (1);
	result = ft_atoi(argv[1]);
	result2 = atoi(argv[1]);
	printf("(MY FUNCTION) %i.\n", result);
	printf("(ORIGINAL) %i.\n", result2);
	return (0);
}*/

int	ft_atoi(const char *nptr)
{
	int	index;
	int	signal;
	int	result;
	int	count;

	index = 0;
	signal = 1;
	result = 0;
	count = 0;
	while (nptr[index] == ' ' || nptr[index] == '\n' || nptr[index] == '\t'
		|| nptr[index] == '\v' || nptr[index] == '\r' || nptr[index] == '\f')
		index++;
	while (nptr[index] == '-' || nptr[index] == '+')
	{
		count_signal(nptr[index], &signal, &count);
		index++;
	}
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		result *= 10;
		result += (nptr[index] - '0');
		index++;
	}
	return (result * signal);
}

static void	count_signal(char c, int *signal, int *count)
{
	if (c == '-' && *count == 0)
		*signal = -1;
	(*count)++;
	if (*count > 1)
		*signal = 0;
}
