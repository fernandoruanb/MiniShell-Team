/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:16:31 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/12 08:16:32 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

/*void	*ft_memset(void *s, int c, size_t n);

int	main(int argc, char **argv)
{
	char	*result;
	//char	*result2;

	if (argc < 4)
		return (1);
	result = ft_memset(argv[1], argv[2][0], atoi(argv[3]));
	//result2 = memset(argv[1], argv[2][0], atoi(argv[3]));
	printf("(MY FUNCTION) %s.\n", result);
	//printf("(ORIGINAL) %s.\n", result2);
	return (0);
}*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			index;

	ptr = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		ptr[index] = (unsigned char)c;
		index++;
	}
	return (s);
}
