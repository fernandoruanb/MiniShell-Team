/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:58:08 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/24 14:58:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*find_path(char *cmd, char **paths)
{
	char	*true_temp;
	char	*true_path;
	int		index;

	index = 0;
	while (paths[index])
	{
		true_temp = ft_strjoin(paths[index], "/");
		if (!true_temp)
			return (NULL);
		true_path = ft_strjoin(true_temp, cmd);
		if (!true_path)
			return (NULL);
		if (access(true_path, F_OK | R_OK) == 0)
			return (true_path);
		index++;
	}
	return (NULL);
}
