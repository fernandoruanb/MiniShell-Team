/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-expand_tilde.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:56:53 by jonas             #+#    #+#             */
/*   Updated: 2025/03/13 21:58:18 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(char *str)
{
	char	*buf;

	buf = NULL;
	buf = ft_calloc(1024, 1);
	if (!getcwd(buf, 1024))
		return (str);
	buf = ft_strdup(getenv("HOME"));
	if (!buf)
		return (str);
	free(str);
	return (buf);
}
