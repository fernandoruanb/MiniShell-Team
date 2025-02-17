/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.5-converttosplit_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:21:36 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 16:22:42 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		printf("%s ", split[i++]);
	printf("\n");
}

void	print_array(char ***array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		print_split(array[i++]);
}

void	*clean_array(char ***array)
{
	int	i;

	if (!array)
		return (NULL);
	i = -1;
	while (array[++i])
		clear_split(array[i]);
	return (NULL);
}
