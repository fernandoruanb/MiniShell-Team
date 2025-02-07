/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:54:22 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:54:44 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_absolute_path(t_token *root, t_utils *data)
{
	if (access(root->str, F_OK | X_OK) == 0)
	{
		data->status = 1;
		return (1);
	}
	return (0);
}
