/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:10:27 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/12 10:10:29 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

/*char	*ft_strrchr(const char *s, int c);

int	main(int argc, char **argv)
{
	char	*result;
	char	*result2;

	if (argc < 3)
		return (1);
	result = ft_strrchr(argv[1], argv[2][0]);
	result2 = strrchr(argv[1], argv[2][0]);
	printf("(MY FUNCTION) %s.\n", result);
	printf("(ORIGINAL) %s.\n", result2);
	return (0);
}*/

char	*ft_strrchr(const char *s, int c)
{
	int	length;

	length = ft_strlen(s);
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[length]);
	while (length >= 0)
	{
		if (s[length] == (unsigned char)c)
			return ((char *)&s[length]);
		length--;
	}
	return (NULL);
}
