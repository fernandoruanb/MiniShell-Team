/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:05:07 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/11 12:05:08 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>*/

//int	ft_isascii(int c);

/*int	main(int argc, char **argv)
{
	int	result;
	int	result2;

	if (argc < 2)
		return (1);
	result = ft_isascii(argv[1][0]);
	result = isascii(argv[1][0]);
	printf("(MY FUNCTION) %i.\n", result);
	printf("(ORIGINAL) %i.\n", result2);
	return (0);
}*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
