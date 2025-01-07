/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:19:11 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/21 09:40:54 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	union_display(const char *s1, const char *s2);

int	main(int argc, char **argv)
{
	if (argc < 3 || argc > 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	union_display(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}*/

void	union_display(const char *s1, const char *s2)
{
	char	buffer[256];
	int		index;
	int		s_index;
	int		count;

	index = 0;
	s_index = 0;
	count = 0;
	while (s1[index] != '\0')
	{
		write(1, &s1[index], 1);
		index++;
	}
	while (s2[s_index] != '\0')
	{
		if (!ft_strchr(s1, s2[s_index]) && !ft_strchr(buffer, s2[s_index]))
		{
			buffer[count] = s2[s_index];
			write(1, &s2[s_index], 1);
			count++;
		}
		s_index++;
	}
}
