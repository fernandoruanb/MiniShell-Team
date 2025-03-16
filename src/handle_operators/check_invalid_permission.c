/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_permission.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:08:43 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/16 11:23:35 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_invalid_permission(char *f)
{
	if (access(f, F_OK) == 0)
	{
		if (access(f, W_OK) == -1)
			return (1);
	}
	return (0);
}

