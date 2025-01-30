/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:12:43 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/30 11:33:24 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	ft_env(t_data *data)
{
	int	index;

	index = 0;
	while (data->envp[index] != NULL)
	{
		ft_printf("%s\n", data->envp[index]);
		index++;
	}
	data->status = 0;
}
