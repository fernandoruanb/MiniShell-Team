/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:10:48 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/15 17:10:50 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

//static char	ft_toupper_i(unsigned int index, char c);

/*char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int	main(int argc, char **argv)
{
	char	*result;

	if (argc < 2)
		return (1);
	printf("A string bonita para teste foi: %s.\n", argv[1]);
	result = ft_strmapi(argv[1], &ft_toupper_i);
	printf("(MY FUNCTION) %s.\n", result);
	return (0);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	unsigned int	length;
	char			*buffer;

	index = 0;
	length = ft_strlen(s);
	buffer = (char *)malloc(length + 1);
	if (!buffer)
		return (NULL);
	while (s[index] != '\0')
	{
		buffer[index] = f(index, s[index]);
		index++;
	}
	buffer[index] = '\0';
	return (buffer);
}

/*static char	ft_toupper_i(unsigned int index, char c)
{
	if ((index % 2 == 0) && (c >= 'a' && c <= 'z'))
		return (c - ('a' - 'A'));
	return (c);
}*/
