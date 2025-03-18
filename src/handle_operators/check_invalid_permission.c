/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_permission.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:08:43 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/17 20:01:23 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_invalid_permission(char *f)
{
	if (access(f, F_OK) == 0)
	{
		if (access(f, W_OK) == -1)
		{
			ft_putstr_fd(" Permission denied\n", 2);
			return (1);
		}
	}
	return (0);
}
