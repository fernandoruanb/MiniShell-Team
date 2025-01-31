/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:05:00 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/19 09:20:37 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	inter(const char *s1, const char *s2);

int	main(int argc, char **argv)
{
	if (argc < 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}*/

void	inter(const char *s1, const char *s2)
{
	char	array[256];
	int		index;
	int		s_index;

	index = 0;
	s_index = 0;
	while (s1[index] != '\0')
	{
		if (ft_strchr(s2, s1[index]) && !ft_strchr(array, s1[index]))
		{
			write(1, &s1[index], 1);
			array[s_index] = s1[index];
			s_index++;
		}
		index++;
	}
}
