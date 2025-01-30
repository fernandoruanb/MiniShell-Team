/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:43:22 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/13 10:43:24 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>*/
#include "libft.h"

/*void	*ft_memchr(const void *s, int c, size_t n);

int	main(int argc, char **argv)
{
	char	*result;
	char	*result2;

	if (argc < 2)
		return (1);
	result = ft_memchr(argv[1], argv[2][0], atoi(argv[3]));
	result2 = memchr(argv[1], argv[2][0], atoi(argv[3]));
	printf("(MY FUNCTION) %s.\n", result);
	printf("(ORIGINAL) %s.\n", result2);
	return (0);
}*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	size_t				index;

	index = 0;
	ptr = (const unsigned char *)s;
	while (index < n)
	{
		if (ptr[index] == (unsigned char)c)
			return ((char *)&ptr[index]);
		index++;
	}
	return (NULL);
}
