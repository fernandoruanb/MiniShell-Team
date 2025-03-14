/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8-env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:09:39 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/14 18:09:03 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data)
{
	if (!data)
		return (1);
	print_split(data->original_envp);
	return (1);
}
