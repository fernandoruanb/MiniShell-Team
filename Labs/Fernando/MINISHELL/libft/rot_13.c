/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:04:13 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/17 15:34:09 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	rot_13(char letter);

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
		rot_13(argv[1][index]);
		index++;
	}
	write(1, "\n", 1);
	return (0);
}*/

void	rot_13(char letter)
{
	char	*alphabet_l;
	char	*alphabet_u;
	int		index;
	int		s_index;

	index = 0;
	alphabet_l = "abcdefghijklmnopqrstuvwxyz";
	alphabet_u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	s_index = 0;
	if ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z'))
		write(1, &letter, 1);
	while (alphabet_l[index] != letter && alphabet_l[index] != '\0')
		index++;
	if (alphabet_l[index] == letter)
		write(1, &alphabet_l[(index + 13) % 26], 1);
	while (alphabet_u[s_index] != letter && alphabet_u[s_index] != '\0')
		s_index++;
	if (alphabet_u[s_index] == letter)
		write(1, &alphabet_u[(s_index + 13) % 26], 1);
}
