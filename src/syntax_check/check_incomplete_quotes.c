/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_incomplete_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:56:09 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/15 18:56:42 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_incomplete_quotes(char *filename)
{
	int	index;
	int	double_quotes;
	int	simple_quotes;

	index = 0;
	double_quotes = 0;
	simple_quotes = 0;
	while (filename[index] != '\0')
	{
		if (filename[index] == '\'')
			simple_quotes++;
		else if (filename[index] == '\"')
			double_quotes++;
		index++;
	}
	if (double_quotes % 2 != 0 || simple_quotes % 2 != 0)
		return (1);
	return (0);
}
