/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:24:58 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/17 16:41:55 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	rotone(char letter);

int	main(int argc, char **argv)
{
	int	index;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	index = 0;
	while (argv[1][index] != '\0')
	{
		rotone(argv[1][index]);
		index++;
	}
	write(1, "\n", 1);
	return (0);
}*/

void	rotone(char letter)
{
	char	*alphabet_l;
	char	*alphabet_u;
	int		index;
	int		s_index;

	alphabet_l = "abcdefghijklmnopqrstuvwxyz";
	alphabet_u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	index = 0;
	s_index = 0;
	if ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z'))
	{
		write(1, &letter, 1);
		return ;
	}
	while (alphabet_l[index] != letter && alphabet_l[index] != '\0')
		index++;
	if (alphabet_l[index] == letter)
		write(1, &alphabet_l[(index + 1) % 26], 1);
	while (alphabet_u[s_index] != letter && alphabet_u[s_index] != '\0')
		s_index++;
	if (alphabet_u[s_index] == letter)
		write(1, &alphabet_u[(s_index + 1) % 26], 1);
}
