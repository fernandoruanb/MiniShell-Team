/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:13:20 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/30 14:23:58 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	last_word(const char *s);

int	main(int argc, char **argv)
{
	if (argc < 2 || argc > 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	last_word(argv[1]);
	write(1, "\n", 1);
	return (1);
}*/

void	last_word(const char *s)
{
	size_t	count;
	size_t	length;
	size_t	index;

	if (!s)
		return ;
	length = ft_strlen(s);
	count = 0;
	while (length > 0 && (s[length - 1] == ' ' || s[length - 1] == '\t'))
		length--;
	while (length > 0 && (s[length - 1] != ' ' && s[length - 1] != '\t'))
	{
		count++;
		length--;
	}
	index = 0;
	while (index < count)
	{
		write(1, &s[length], 1);
		index++;
		length++;
	}
}
