/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 08:28:55 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/19 08:39:16 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>
#include <stdio.h>

size_t	ft_strspn(const char *s, const char *accept);

int	main(int argc, char **argv)
{
	size_t	result;
	size_t	result2;

	if (argc < 2)
		return (1);
	result = ft_strspn(argv[1], argv[2]);
	result2 = strspn(argv[1], argv[2]);
	printf("(MY FUNCTION) %zu\n", result);
	printf("(ORIGINAL) %zu\n", result2);
	return (0);
}*/

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = 0;
	while (s[index] != '\0')
	{
		if (ft_strchr(accept, s[index]))
			length++;
		if (!ft_strchr(accept, s[index + 1]))
			break ;
		index++;
	}
	return (length);
}
