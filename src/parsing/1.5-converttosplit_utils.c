/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.5-converttosplit_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:21:36 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/18 11:45:05 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(t_id id)
{
	return (id == PIPE || id == OPERATOR_AND || id == OPERATOR_OR);
}

void	print_array(char ***array)
{
	int	i;
	int	j;

	if (!array || !*array)
		return ;
	i = -1;
	while (array[++i])
	{
		j = -1;
		printf("%d | ", i);
		while (array[i][++j])
			printf("%s[%d]\t", array[i][j], j);
		printf("\n");
	}
}

void	*clean_array(char ***array) {
    int	i;
	int	j;

	if (!array || !*array)
		return (NULL);
	i = 0;
    while (array[i])
	{
        j = 0;
        while (array[i][j])
            free(array[i][j++]);
		free(array[i++]);
    }
    free(array);
	return (NULL);
}
