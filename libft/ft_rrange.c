/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:56:08 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/22 16:09:22 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	*ft_rrange(int start, int end);

int	main(int argc, char **argv)
{
	int	index;
	int	len;
	int	*result;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	len = ft_abs(ft_atoi(argv[2]) - ft_atoi(argv[1])) + 1;
	result = ft_rrange(ft_atoi(argv[1]), ft_atoi(argv[2]));
	while (index < len)
	{
		if (index < len - 1)
			ft_printf("%d, ", result[index]);
		else
			ft_printf("%d.\n", result[index]);
		index++;
	}
	return (0);
}*/

int	*ft_rrange(int start, int end)
{
	int	index;
	int	len;
	int	*result;

	len = ft_abs(end - start) + 1;
	result = (int *)malloc(sizeof(int) * len);
	if (!result)
		return (0);
	index = 0;
	while (index < len)
	{
		if (start < end)
		{
			result[index] = end;
			end--;
		}
		else
		{
			result[index] = end;
			end++;
		}
		index++;
	}
	return (result);
}
