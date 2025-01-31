/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdmatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:54:03 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/21 12:08:34 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	wdmatch(const char *s1, const char *s2);

int	main(int argc, char **argv)
{
	if (argc < 3 || argc > 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	wdmatch(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}*/

void	wdmatch(const char *s1, const char *s2)
{
	int		index;
	int		s_index;
	size_t	length;

	index = 0;
	s_index = 0;
	length = ft_strlen(s1);
	while (s1[index] != '\0' && s2[s_index] != '\0')
	{
		if (s1[index] == s2[s_index])
		{
			index++;
			s_index = 0;
			if (s1[index] == '\0')
				write(1, s1, length);
		}
		s_index++;
	}
}
