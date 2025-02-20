/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-expand_tilde.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:56:53 by jonas             #+#    #+#             */
/*   Updated: 2025/02/20 10:35:05 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home(char *buf)
{
	int		i;
	char	*new;
	int		slash;

	i = -1;
	slash = 3;
	while (buf[++i] && slash)
		slash -= (buf[i] == '/');
	new = ft_strndup(buf, i - 1);
	if (!new)
		return(NULL);
	free(buf);
	return (new);
}

char	*expand_tilde(char *str)
{
	char	*buf = NULL;

	buf = ft_calloc(1024, 1);
	if (!getcwd(buf, 1024))
		return (str);
	buf = get_home(buf);
	if (!buf)
		return (str);
	free(str);
	return (buf);
}
