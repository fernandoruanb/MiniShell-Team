/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:30:48 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/07 12:31:01 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_builtins(t_token *root)
{
	if (ft_strcmp(root->str, "cd") == 0)
		return (1);
	else if (ft_strcmp(root->str, "export") == 0)
		return (1);
	else if (ft_strcmp(root->str, "unset") == 0)
		return (1);
	else if (ft_strcmp(root->str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(root->str, "env") == 0)
		return (1);
	else if (ft_strcmp(root->str, "echo") == 0)
		return (1);
	else if (ft_strcmp(root->str, "exit") == 0)
		return (1);
	else if (ft_strcmp(root->str, "clear") == 0)
		return (1);
	return (0);
}
