/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:21:03 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/17 08:21:05 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/*char	*ft_strjoin(char const *s1, char const *s2);

int	main(int argc, char **argv)
{
	char	*result;

	if (argc < 3)
		return (1);
	result = ft_strjoin(argv[1], argv[2]);
	printf("(MY FUNCTION) %s.\n", result);
	free(result);
	return (0);
}*/

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len_dst;
	int		len_src;
	char	*buffer;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	len_dst = ft_strlen(s1);
	len_src = ft_strlen(s2);
	buffer = (char *)malloc((len_dst + len_src) + 1);
	if (!buffer)
		return (NULL);
	index = 0;
	while (*s1)
		buffer[index++] = *s1++;
	while (*s2)
		buffer[index++] = *s2++;
	buffer[len_dst + len_src] = '\0';
	return (buffer);
}
