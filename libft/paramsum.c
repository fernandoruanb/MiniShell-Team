/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:03:14 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/23 13:07:30 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	paramsum(int argc);

int	main(int argc, char **argv)
{
	int	result;

	result = paramsum(argc);
	ft_printf("O número de argumentos é: %d\n", result);
	return (0);
}*/

int	paramsum(int argc)
{
	return (argc - 1);
}
