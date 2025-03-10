/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:34:41 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/10 12:42:05 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data)
{
	char	*path;

	if (!data)
		return (1);
	path = ft_calloc(1024, 1);
	getcwd(path, 1024);
	printf("%s\n", path);
	free(path);
	return (1);
}
