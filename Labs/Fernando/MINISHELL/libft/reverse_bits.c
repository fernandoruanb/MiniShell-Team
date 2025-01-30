/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:28:47 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/20 18:53:12 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>

char	reverse_bits(char octet);

int	main(void)
{
	char	result;

	result = reverse_bits(2);
	printf("%d\n", result);
	return (0);
}*/

char	reverse_bits(char octet)
{
	int		index;
	char	result;

	index = 8;
	result = 0;
	while (index--)
	{
		result = (result << 1) | (octet & 1);
		octet >>= 1;
	}
	return (result);
}
