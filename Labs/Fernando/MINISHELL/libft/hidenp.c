/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidenp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:52:23 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/22 18:58:01 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	hidenp(const char *s1, const char *s2);

int	main(int argc, char **argv)
{
	if (argc < 3 || argc > 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	hidenp(argv[1], argv[2]);
	return (0);
}*/

void	hidenp(const char *s1, const char *s2)
{
	int	index;
	int	s_index;

	index = 0;
	s_index = 0;
	while (s1[index] && s2[s_index])
	{
		if (s1[index] == s2[s_index])
			index++;
		s_index++;
	}
	if (s1[index] == '\0')
		write(1, "1", 1);
	else
		write(1, "0", 1);
	write(1, "\n", 1);
}
