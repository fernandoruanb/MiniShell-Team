/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:27:55 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/28 11:30:34 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>*/
#include "libft.h"

/*int	ft_strncmp(const char *s1, const char *s2, size_t n);

int	main(int argc, char **argv)
{
	int	result;
	int	result2;

	if (argc < 4)
		return (1);
	result = ft_strncmp(argv[1], argv[2], atoi(argv[3]));
	result2 = strncmp(argv[1], argv[2], atoi(argv[3]));
	printf("(MY FUNCTION) %i.\n", result);
	printf("(ORIGINAL) %i.\n", result2);
	return (0);
}*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	if (!s1 || !s2)
		return (INT_MIN);
	index = 0;
	while (s1[index] != '\0' && s2[index] != '\0' && index < n)
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	if (index < n)
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	return (0);
}
