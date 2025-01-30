/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:34:25 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/30 11:32:18 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	free_shell(t_data *data)
{
	if (data->oldpwd != NULL)
		free(data->oldpwd);
	if (data->newpwd != NULL)
		free(data->newpwd);
	if (data->line != NULL)
		free(data->line);
	rl_clear_history();
}
