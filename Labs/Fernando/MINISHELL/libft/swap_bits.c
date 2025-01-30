/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 08:29:38 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/21 08:40:07 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	swap_bits(char octet);

int	main(void)
{
	char	result;

	result = swap_bits(255);
	ft_printf("%c\n", result);
	return (0);
}*/

char	swap_bits(char octet)
{
	return (octet << 4 | octet >> 4);
}
