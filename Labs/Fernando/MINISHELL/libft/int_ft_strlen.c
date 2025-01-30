/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_ft_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 09:24:03 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/24 09:31:19 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "libft.h"

int	int_ft_strlen(const char *str);

int	main(int argc, char **argv)
{
	int	result;

	if (argc < 2)
		return (1);
	result = int_ft_strlen(argv[1]);
	ft_printf("%d\n", result);
	return (0);
}*/

int	int_ft_strlen(const char *str)
{
	int	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}
