/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:01:26 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/19 09:24:21 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strrev(char *str);

int	main(void)
{
	char	str[8] = "Hello";
	char	*result;

	ft_printf("A string bonita para teste: %s\n", str);
	result = ft_strrev(str);
	ft_printf("Resultado: %s\n", result);
	return (0);
}*/

char	*ft_strrev(char *str)
{
	size_t	index;
	size_t	length;
	char	temp;

	index = 0;
	length = ft_strlen(str);
	while (index < length)
	{
		temp = str[index];
		str[index] = str[length - 1];
		str[length - 1] = temp;
		index++;
		length--;
	}
	return (str);
}
