/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_builtins_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:26:21 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:26:42 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_builtins_quotes(t_utils *data)
{
	if (ft_strcmp(data->new_str, "cd") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "export") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "unset") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "env") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "echo") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "exit") == 0)
		return (1);
	else if (ft_strcmp(data->new_str, "clear") == 0)
		return (1);
	return (0);
}
