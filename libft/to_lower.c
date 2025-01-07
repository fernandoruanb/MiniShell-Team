/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lower.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:43:59 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/22 10:47:57 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "libft.h"

char	to_lower(const char c);

int	main(int argc, char **argv)
{
	char	c;

	if (argc < 2)
		return (1);
	c = to_lower(argv[1][0]);
	ft_printf("%c\n", c);
	return (0);
}*/

char	to_lower(const char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}
