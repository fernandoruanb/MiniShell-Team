/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:55:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/10 10:50:40 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_full_path(t_token *root, int index, t_utils *data)
{
	if (data->temp)
		free(data->temp);
	if (data->path)
		free(data->path);
	data->path = NULL;
	data->temp = NULL;
	data->temp = ft_strjoin(data->paths[index], "/");
	if (!data->temp)
		return ;
	data->path = ft_strjoin(data->temp, root->str);
}
