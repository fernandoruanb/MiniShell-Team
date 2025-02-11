/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:29:07 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/11 14:27:06 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_program(t_token *root, t_utils *data)
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
	if (root)
		free_tokens(root);
}
