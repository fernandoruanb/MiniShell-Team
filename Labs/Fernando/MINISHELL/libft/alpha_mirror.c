/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alpha_mirror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 08:23:02 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/18 08:38:45 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	alpha_mirror(char *c);

int	main(int argc, char **argv)
{
	size_t	index;
	size_t	length;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	length = ft_strlen(argv[1]);
	index = 0;
	while (argv[1][index] != '\0')
	{
		alpha_mirror(&argv[1][index]);
		index++;
	}
	write(1, argv[1], length);
	write(1, "\n", 1);
	return (0);
}*/

void	alpha_mirror(char *c)
{
	char	*alphabet_l;
	char	*alphabet_u;
	int		index;
	int		s_index;

	alphabet_l = "abcdefghijklmnopqrstuvwxyz";
	alphabet_u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	index = 0;
	s_index = 0;
	while (alphabet_l[index] != *c && alphabet_l[index] != '\0')
		index++;
	if (alphabet_l[index] == *c)
		*c = alphabet_l[25 - index];
	while (alphabet_u[s_index] != *c && alphabet_u[s_index] != '\0')
		s_index++;
	if (alphabet_u[s_index] == *c)
		*c = alphabet_u[25 - s_index];
}
