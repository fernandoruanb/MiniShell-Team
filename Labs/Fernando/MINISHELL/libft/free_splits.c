/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_splits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:02:04 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/28 13:15:49 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_line(char *line)
{
	if (line)
		free(line);
}

int	free_splits(char *l, char **split1, char **split2, char **split3)
{
	int	index;

	check_line(l);
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
