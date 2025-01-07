/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:50:27 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/20 17:23:29 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*void	print_bits(unsigned char octet);

int	main(void)
{
	print_bits(2);
	return (0);
}*/

void	print_bits(unsigned char octet)
{
	int		index;
	char	bit;

	index = 8;
	while (index--)
	{
		bit = (((octet >> index) & 1) + '0');
		write(1, &bit, 1);
	}
}
