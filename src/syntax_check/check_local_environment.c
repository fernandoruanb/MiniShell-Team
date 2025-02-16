/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_local_environment.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:07:11 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/16 18:33:14 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_local_environment(t_token *root)
{
	int	index;

	index = 0;
	if (root->str[index] == '=')
		return (0);
	index = 1;
	while (root->str[index] != '\0')
	{
		if (root->str[index] == '=')
			return (1);
		index++;
	}
	return (0);
}
