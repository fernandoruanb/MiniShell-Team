/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decision_of_emperor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:35:51 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/18 13:14:15 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	decision_of_emperor(t_token *root, t_utils *data)
{
	if (root->str[0] == '/' || root->str[0] == '.')
		if (access(root->str, F_OK) == -1)
			return (show_error_fd(" No such file or directory",
					0, data, 127));
	return (show_error_fd(" command not found", 0, data, 127));
}
