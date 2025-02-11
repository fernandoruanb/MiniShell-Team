/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_builtins_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:26:21 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/11 16:59:10 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_builtins_quotes(t_utils *data)
{
	if (ft_strcmp(data->copy_new, "cd") == 0)
		return (1);
	else if (ft_strcmp(data->copy_new, "export") == 0)
		return (1);
	else if (ft_strcmp(data->copy_new, "unset") == 0)
		return (1);
	else if (ft_strcmp(data->copy_new, "pwd") == 0)
		return (1);
	else if (ft_strcmp(data->copy_new, "env") == 0)
		return (1);
	else if (ft_strcmp(data->copy_new, "echo") == 0)
		return (1);
	else if (ft_strcmp(data->copy_new, "exit") == 0)
		return (1);
	else if (ft_strcmp(data->copy_new, "clear") == 0)
		return (1);
	return (0);
}
