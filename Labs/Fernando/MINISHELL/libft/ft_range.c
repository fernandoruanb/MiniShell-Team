/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:50:18 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/22 15:18:33 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	*ft_range(int start, int end);

int	main(int argc, char **argv)
{
	int	index;
	int	len;
	int	*result;

	if (argc < 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	result = ft_range(ft_atoi(argv[1]), ft_atoi(argv[2]));
	index = 0;
	len = ft_abs(ft_atoi(argv[2]) - ft_atoi(argv[1])) + 1;
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

int	*ft_range(int start, int end)
{
	int	len;
	int	*result;
	int	index;

	len = ft_abs(end - start) + 1;
	result = (int *)malloc(sizeof(int) * len);
	if (!result)
		return (0);
	index = 0;
	while (index < len)
	{
		if (start < end)
		{
			result[index] = start;
			start++;
		}
		else
		{
			result[index] = start;
			start--;
		}
		index++;
	}
	return (result);
}
