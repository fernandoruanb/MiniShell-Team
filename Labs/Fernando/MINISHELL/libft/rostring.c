/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:46:14 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/24 12:36:51 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*void	rostring(const char *str, int index, int count);

int	main(int argc, char **argv)
{
	int	index;
	int	count;

	while (argc < 2 || argc > 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	index = 0;
	count = 0;
	while ((argv[1][index]) && (argv[1][index] == ' '
		|| argv[1][index] == '\t'))
		index++;
	count = index;
	while ((argv[1][index]) && (argv[1][index] != ' '
		&& argv[1][index] != '\t'))
		index++;
	rostring(argv[1], index, count);
	return (0);
}*/

void	rostring(const char *str, int index, int count)
{
	int	save;

	save = index;
	while (str[index] != '\0')
	{
		while ((str[index]) && (str[index] == ' ' || str[index] == '\t'))
			index++;
		while ((str[index]) && (str[index] != ' ' && str[index] != '\t'))
		{
			write(1, &str[index], 1);
			index++;
		}
		if (str[index - 1] == ' ')
			break ;
		write(1, " ", 1);
	}
	while (count < save)
	{
		write(1, &str[count], 1);
		count++;
	}
	write(1, "\n", 1);
}
