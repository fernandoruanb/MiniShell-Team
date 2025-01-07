/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:06:52 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/17 12:26:32 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_index(char *alphabet_l, char *alphabet_u, char letter);

void		repeat_alpha(const char *str);

/*int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	repeat_alpha(argv[1]);
	return (0);
}*/

void	repeat_alpha(const char *str)
{
	char	*alphabet_l;
	char	*alphabet_u;
	int		times;
	int		index;

	alphabet_l = "abcdefghijklmnopqrstuvwxyz";
	alphabet_u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	index = 0;
	while (str[index] != '\0')
	{
		times = find_index(alphabet_l, alphabet_u, str[index]);
		if (times == -1)
			write(1, &str[index], 1);
		while (times > 0)
		{
			write(1, &str[index], 1);
			times--;
		}
		index++;
	}
	write(1, "\n", 1);
}

static int	find_index(char *alphabet_u, char *alphabet_l, char letter)
{
	int	index;
	int	s_index;

	index = 0;
	s_index = 0;
	while (alphabet_l[index] != letter && alphabet_l[index] != '\0')
		index++;
	index++;
	if (alphabet_l[index - 1] == letter)
		return (index);
	while (alphabet_u[s_index] != letter && alphabet_u[s_index] != '\0')
		s_index++;
	s_index++;
	if (alphabet_u[s_index - 1] == letter)
		return (s_index);
	return (-1);
}
