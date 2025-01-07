/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_int_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 13:15:25 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/12/27 19:45:41 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "libft.h"

void	sort_int_tab(int *tab, unsigned int size);

int	main(void)
{
	int	index;
	int	tab[] = {0, 8, 21, 32, 1, 3};

	sort_int_tab(tab, 6);
	index = 0;
	while (index < 6)
	{
		if (index < 6 - 1)
			ft_printf("%d, ", tab[index]);
		else
			ft_printf("%d.\n", tab[index]);
		index++;
	}
	return (0);
}*/

int	*sort_int_tab(int *tab, unsigned int size)
{
	unsigned int	index;
	unsigned int	temp;

	index = 0;
	while (index < (size - 1))
	{
		if (tab[index] > tab[index + 1])
		{
			temp = tab[index];
			tab[index] = tab[index + 1];
			tab[index + 1] = temp;
			index = 0;
		}
		else
			index++;
	}
	return (tab);
}
