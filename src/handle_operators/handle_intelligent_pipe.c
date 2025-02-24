/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_intelligent_pipe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:56:12 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/24 12:00:55 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_intelligent_pipe(t_token *root, t_utils *data)
{
	t_token *last;

	data->pipes = get_pipes(root);
	if (data->pipes != 0)
		init_pipes(data);
	last = root;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	handle_intelligent_pipe(data->token, &data->utils, "/bin/echo oi");
	return (0);
}
