/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_all_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:25:07 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/11 13:45:47 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	test_all_paths(t_utils *data)
{
	int	index;

	index = 0;
	while (data->paths[index] != NULL)
	{
		if (data->temp)
			free(data->temp);
		if (data->path)
			free(data->path);
		data->temp = ft_strjoin(data->paths[index], "/");
		if (!data->temp)
			return (0);
		data->path = ft_strjoin(data->temp, data->copy_new);
		if (!data->path)
			return (0);
		if (access(data->path, F_OK | X_OK) == 0)
			return (1);
		index++;
	}
	if (case_builtins_quotes(data))
		return (1);
	if (is_absolute_path_quotes(data))
		return (1);
	return (0);
}
