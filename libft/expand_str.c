/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:05:36 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/21 19:31:59 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	expand_str(const char *str);

int	main(int argc, char **argv)
{
	if (argc < 2 || argc > 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	expand_str(argv[1]);
	write(1, "\n", 1);
	return (0);
}*/

void	expand_str(const char *str)
{
	int	index;
	int	count;

	index = 0;
	while (str[index] != '\0')
	{
		count = 0;
		if (str[index] == ' ' || str[index] == '\t')
			index++;
		if ((index - 1 != 0 && str[index] != ' ' && str[index] != '\t')
			&& (str[index - 1] == ' ' || str[index - 1] == '\t'))
		{
			while (count < 4)
			{
				write(1, " ", 1);
				count++;
			}
			write(1, &str[index], 1);
		}
		else if (str[index] != ' ' && str[index] != '\t')
			write(1, &str[index], 1);
		index++;
	}
}
