/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:02:04 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/24 15:02:18 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_splits(char **split1, char **split2, char **split3)
{
	int	index;

	if (split1)
	{
		index = 0;
		while (split1[index])
			free(split1[index++]);
		free(split1);
	}
	if (split2)
	{
		index = 0;
		while (split2[index])
			free(split2[index++]);
		free(split2);
	}
	if (split3)
	{
		index = 0;
		while (split3[index])
			free(split3[index++]);
		free(split3);
	}
	return (1);
}
