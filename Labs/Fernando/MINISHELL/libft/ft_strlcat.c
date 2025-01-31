/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:56:04 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/16 18:56:04 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/*size_t	ft_strlcat(char *dst, const char *src, size_t size);

int	main(int argc, char **argv)
{
	int	result;

	if (argc < 4)
		return (1);
	result = ft_strlcat(argv[1], argv[2], atoi(argv[3]));
	printf("(MY FUNCTION) %i.\n", result);
	return (0);
}*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	index;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	index = 0;
	if (len_dst >= size)
		return (size + len_src);
	while ((len_dst + index) < (size - 1) && src[index] != '\0')
	{
		dst[len_dst + index] = src[index];
		index++;
	}
	dst[len_dst + index] = '\0';
	return (len_dst + len_src);
}
