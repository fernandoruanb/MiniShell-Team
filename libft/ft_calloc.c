/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:01:52 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/14 14:01:56 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

/*void	*ft_calloc(size_t nmemb, size_t size);

int	main(int argc, char **argv)
{
	char	*buffer;
	int	nmemb;
	int	size;

	nmemb = atoi(argv[1]);
	size = atoi(argv[2]);
	buffer = ft_calloc(nmemb, size);
	if (!buffer)
		printf("Error!!! Buffer não criado.\n");
	else
		printf("Buffer criado e zerado com sucesso.\n");
	return (0);
}*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			length;
	void			*buffer;
	unsigned char	*ptr;
	size_t			index;

	index = 0;
	if (nmemb != 0 && size > (size_t) - 1 / nmemb)
		return (NULL);
	length = nmemb * size;
	buffer = malloc(length);
	if (!buffer)
		return (NULL);
	ptr = (unsigned char *)buffer;
	while (index < length)
	{
		ptr[index] = 0;
		index++;
	}
	return (buffer);
}
