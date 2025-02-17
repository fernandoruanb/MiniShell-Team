/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camel_to_snake.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:20:22 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 12:31:00 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isupper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

void	camel_to_snake(char *str)
{
	int		i;
	int		convert;
	char	*temp;

	temp = str;
	i = -1;
	convert = 0;
	while (temp[++i])
	{
		convert = ft_isupper(temp[i]) * 32;
		if (convert)
			printf("_");
		printf("%c", temp[i] + convert);
	}	
	printf("\n");
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	camel_to_snake(argv[1]);
	return (0);
}
