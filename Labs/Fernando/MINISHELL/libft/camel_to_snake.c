/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camel_to_snake.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:25:27 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/18 10:30:55 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	camel_to_snake(char *str);

int	main(int argc, char **argv)
{
	char	*str;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	str = argv[1];
	camel_to_snake(str);
	write(1, "\n", 1);
	return (0);
}*/

void	camel_to_snake(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] >= 'a' && str[index] <= 'z')
			write(1, &str[index], 1);
		else if (str[index] >= 'A' && str[index] <= 'Z')
		{
			write(1, "_", 1);
			str[index] += 32;
			write(1, &str[index], 1);
		}
		index++;
	}
}
