/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:15:43 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/13 12:15:45 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>*/
#include "libft.h"

/*int	ft_memcmp(const void *s1, const void *s2, size_t n);

int	main(int argc, char **argv)
{
	int	result;
	int	result2;

	if (argc < 2)
		return (1);
	result = ft_memcmp(argv[1], argv[2], atoi(argv[3]));
	result2 = memcmp(argv[1], argv[2], atoi(argv[3]));
	printf("(MY FUNCTION) %i.\n", result);
	printf("(ORIGINAL) %i.\n", result2);
	return (0);
}*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				index;

	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	index = 0;
	if (n == 0)
		return (0);
	while (index < n - 1)
	{
		if (ptr1[index] != ptr2[index])
			return (ptr1[index] - ptr2[index]);
		index++;
	}
	return (ptr1[index] - ptr2[index]);
}
