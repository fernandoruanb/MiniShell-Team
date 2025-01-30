/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:51:02 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/20 16:27:41 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>

int	max(int *tab, unsigned int len);

int	main(void)
{
	int	tab[] = {0, 1, 2, 3, 4, 5, 42};
	unsigned int	len;
	int	result;

	len = 7;
	result = max(tab, len);
	printf("%d\n", result);
	return (0);
}*/

int	max(int *tab, unsigned int len)
{
	int				result;
	unsigned int	index;

	index = 0;
	result = 0;
	while (index < len)
	{
		if (tab[index] > result)
			result = tab[index];
		index++;
	}
	return (result);
}
