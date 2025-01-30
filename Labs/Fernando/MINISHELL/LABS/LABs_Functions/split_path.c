/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:23:52 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/25 19:36:36 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**split_path(int argc, char **argv, char **envp)
{
	int		index;
	char	**paths;

	(void)argc;
	(void)argv;
	index = 0;
	while (!ft_strnstr(envp[index], "PATH", 4) && envp[index])
		index++;
	if (!envp[index])
		return (ft_putendl_fd_n("Impossible to find PATH", 2));
	paths = ft_split(envp[index], ' ');
	if (!paths)
		return (ft_putendl_fd_n("Error alocanting splits", 2));
	return (paths);
}
