/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:40:46 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/12/23 12:39:11 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/*char	*ft_substr(char const *s, unsigned int start, size_t len);

int	main(int argc, char **argv)
{
	char	*result;

	if (argc < 4)
		return (1);
	result = ft_substr(argv[1], atoi(argv[2]), atoi(argv[3]));
	printf("(MY FUNCTION) %s.\n", result);
	return (0);
}*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*buffer;
	size_t	index;

	if (!s)
		return (ft_calloc(1, sizeof(char)));
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_calloc(1, sizeof(char)));
	if (start + len > len_s)
		len = len_s - start;
	buffer = (char *)malloc(len + 1);
	if (!buffer)
		return (NULL);
	index = 0;
	while (index < len)
	{
		buffer[index] = s[start];
		index++;
		start++;
	}
	buffer[index] = '\0';
	return (buffer);
}
