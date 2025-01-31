/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:27:59 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/17 08:32:30 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	first_word(int argc, char **argv);

int	main(int argc, char **argv)
{
	first_word(argc, argv);
	return (0);
}*/

void	first_word(int argc, char **argv)
{
	int	index;

	if (argc < 2 || argc > 2)
	{
		write(1, "\n", 1);
		return ;
	}
	index = 0;
	while ((argv[1][index] == ' ' || argv[1][index] == '\t'))
		index++;
	while ((argv[1][index] != ' ' && argv[1][index] != '\t')
		&& argv[1][index] != '\0')
	{
		write(1, &argv[1][index], 1);
		index++;
	}
	write(1, "\n", 1);
}
