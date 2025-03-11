/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:29:07 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/11 12:30:28 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_program(t_utils *data)
{
	if (data->temp)
		free(data->temp);
	if (data->path)
		free(data->path);
	if (data->copy_new)
		free(data->copy_new);
	if (data->paths)
		free_splits(NULL, data->paths, NULL, NULL);
	if (data->new_str)
		free(data->new_str);
	data->temp = NULL;
	data->path = NULL;
	data->copy_new = NULL;
	data->paths = NULL;
	data->new_str = NULL;
}
