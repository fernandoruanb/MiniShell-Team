/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:59:11 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/28 14:08:41 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*void	str_capitalizer(char *str);

int	main(int argc, char **argv)
{
	int	index;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	index = 1;
	while (index < argc)
	{
		str_capitalizer(argv[index]);
		write(1, "\n", 1);
		index++;
	}
	return (0);
}*/

void	str_capitalizer(char *str)
{
	int	index;

	index = 0;
	if (str[index] >= 'a' && str[index] <= 'z')
		str[index] -= 32;
	write(1, &str[index], 1);
	index++;
	while (str[index] != '\0')
	{
		if (str[index] >= 'A' && str[index] <= 'Z')
			str[index] += 32;
		if ((str[index] >= 'a' && str[index] <= 'z')
			&& (str[index - 1] == ' ' || str[index - 1] == '\t'))
			str[index] -= 32;
		write(1, &str[index], 1);
		index++;
	}
}
