/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 09:05:09 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/24 09:39:52 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	rev_wstr(const char *str);

int	main(int argc, char **argv)
{
	if (argc < 2 || argc > 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	rev_wstr(argv[1]);
	write(1, "\n", 1);
	return (0);
}*/

void	rev_wstr(const char *str)
{
	int	start;
	int	end;
	int	length;

	length = int_ft_strlen(str);
	while (length > 0)
	{
		while ((length > 0) && (str[length - 1] == ' '
				|| str[length - 1] == '\t'))
			length--;
		end = length - 1;
		while ((length > 0) && (str[length - 1] != ' '
				&& str[length - 1] != '\t'))
			length--;
		start = length;
		while (start <= end)
		{
			write(1, &str[start], 1);
			start++;
		}
		write(1, " ", 1);
	}
}
