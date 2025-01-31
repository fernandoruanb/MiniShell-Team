/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:36:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/12 08:36:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>*/
#include "libft.h"

/*void	ft_bzero(void *s, size_t n);

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	ft_bzero(argv[1], atoi(argv[2]));
	printf("(MY FUNCTION) %s.\n", argv[1]);
	//printf("(ORIGINAL) %s.\n", argv[1]);
	return (0);
}*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			index;

	ptr = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		ptr[index] = 0;
		index++;
	}
}
