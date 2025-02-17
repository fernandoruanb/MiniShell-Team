/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:08:58 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 12:03:07 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(char **array, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = high;
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(array[j], array[pivot]) <= 0)
		{
			i++;
			swap(&array[i], &array[j]);
		}
		j++;
	}
	swap(&array[i + 1], &array[high]);
	return (i + 1);
}

void	ft_quicksort(char **array, int low, int high)
{
	int	pivot;

	if (!array)
		return ;
	if (low < high)
	{
		pivot = partition(array, low, high);
		ft_quicksort(array, low, pivot - 1);
		ft_quicksort(array, pivot + 1, high);
	}
}
