/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ulstr_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:45:29 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/18 14:57:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	ulstr_v2(char *str);

int	main(int argc, char **argv)
{
	size_t	length;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	length = ft_strlen(argv[1]);
	ulstr(argv[1]);
	return (0);
}*/

void	ulstr_v2(char *str)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = ft_strlen(str);
	while (str[index] != '\0')
	{
		if (str[index] >= 'a' && str[index] <= 'z')
			str[index] -= 32;
		else if (str[index] >= 'A' && str[index] <= 'Z')
			str[index] += 32;
		index++;
	}
	index = 0;
	while (length--)
		write(1, &str[length], 1);
	write(1, "\n", 1);
}
