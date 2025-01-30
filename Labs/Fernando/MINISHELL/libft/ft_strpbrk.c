/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:13:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/18 19:21:51 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <string.h>

char	*ft_strpbrk(const char *s1, const char *s2);

int	main(int argc, char **argv)
{
	char	*result;
	char	*result2;

	if (argc < 3)
		return (1);
	result = ft_strpbrk(argv[1], argv[2]);
	result2 = strpbrk(argv[1], argv[2]);
	ft_printf("(MY FUNCTION) %s\n", result);
	ft_printf("(ORIGINAL) %s\n", result2);
	return (0);
}*/

char	*ft_strpbrk(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] != '\0')
	{
		if (ft_strchr(s2, s1[index]))
			return ((char *)&s1[index]);
		index++;
	}
	return (NULL);
}
