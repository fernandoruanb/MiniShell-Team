/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8-restore_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:31:48 by jonas             #+#    #+#             */
/*   Updated: 2025/03/20 16:32:13 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_redirect(int *original, t_data *data)
{
	if (!original || (original[0] < 0 || original[1] < 0))
		return ;
	make_redir(original[0], 0);
	make_redir(original[1], 1);
	destroy_fd(&original);
	data->utils.can_read = true;
	data->utils.can_write = true;
	data->flags.shoud_restore = !data->flags.shoud_restore;
}
