/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:38:27 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/14 11:38:28 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <unistd.h>*/
#include "libft.h"

/*char	*ft_strdup(const char *s);

int	main(int argc, char **argv)
{
	char	*result;
	char	*result2;
	int	index;

	if (argc < 2)
		return (1);
	result = ft_strdup(argv[1]);
	result2 = strdup(argv[1]);
	index = 0;
	while (result[index] != '\0')
	{
		write(1, &result[index], 1);
		index++;
	}
	index = 0;
	write(1, "\n", 1);
	while (result2[index] != '\0')
	{
		write(1, &result2[index], 1);
		index++;
	}
	write(1, "\n", 1);
	free(result);
	free(result2);
	return (0);
}*/

char	*ft_strdup(const char *s)
{
	char	*buffer;
	int		length;
	int		index;

	index = 0;
	length = ft_strlen(s);
	buffer = (char *)malloc(length + 1);
	if (!buffer)
		return (NULL);
	while (s[index] != '\0')
	{
		buffer[index] = s[index];
		index++;
	}
	buffer[index] = '\0';
	return (buffer);
}
