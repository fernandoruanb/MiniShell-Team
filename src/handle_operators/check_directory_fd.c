/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directory_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:15:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/16 10:41:04 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_is_directory_fd(char *f, t_utils *data)
{
	if (stat(f, &data->stat_check) == -1)
		return (0);
	if (S_ISDIR(data->stat_check.st_mode))
	{
		ft_printf("Fui eu meu amigo\n");
		return (1);
	}
	return (0);
}
