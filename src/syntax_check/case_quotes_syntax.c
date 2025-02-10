/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_quotes_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:43:56 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/10 08:59:00 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	case_quotes_syntax(char	*quote, int marker, int *flag)
{
	static char	buffer[2];
	static int	index = 0;

	if (index > 1)
		index = 0;
	if (index == 0)
		buffer[0] = quote[marker];
	else if (index == 1)
		buffer[1] = quote[marker];
	if (index == 1 || quote[marker + 1] == '\0')
	{
		if (buffer[0] != buffer[1])
			return (0);
	}
	index++;
	*flag = 0;
	return (1);
}
