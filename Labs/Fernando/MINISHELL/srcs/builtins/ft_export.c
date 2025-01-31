/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:49:14 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/29 19:01:34 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_variables(t_data *data)
{
	int	index;

	index = 0;
	while (data->envp[index])
	{
		ft_printf("declare -x %s\n", envp[index]);
		index++;
	}
}

void	ft_export(t_data *data)
{
	size_t	length;

	length = ft_strlen(length);
	if (length == 6)
		print_variables(data);
}
