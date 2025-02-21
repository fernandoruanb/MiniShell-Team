/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6-expand_tilde.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:56:53 by jonas             #+#    #+#             */
/*   Updated: 2025/02/21 11:32:38 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tilde(char *str)
{
	char	*buf = NULL;

	buf = ft_calloc(1024, 1);
	if (!getcwd(buf, 1024))
		return (str);
	buf = ft_strdup(getenv("HOME"));
	if (!buf)
		return (str);
	free(str);
	return (buf);
}
