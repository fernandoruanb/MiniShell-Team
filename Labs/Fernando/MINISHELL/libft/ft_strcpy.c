/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:52:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/17 09:58:53 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strcpy(char *s1, char *s2);

int	main(int argc, char **argv)
{
	char	dest[50];
	char	*result;
	result = ft_strcpy(dest, argv[1]);
	ft_printf("%s\n", result);
	return (0);
}*/

char	*ft_strcpy(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s2[index] != '\0')
	{
		s1[index] = s2[index];
		index++;
	}
	s1[index] = '\0';
	return (s1);
}
