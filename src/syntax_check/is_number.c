/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:38:16 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:38:29 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_number(t_token *root, t_utils *data)
{
	int	index;

	index = 0;
	while (root->str[index] != '\0')
	{
		if (!ft_isdigit(root->str[index]))
			return (0);
		index++;
	}
	data->files--;
	return (1);
}
