/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-tokensort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:47 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/18 12:01:15 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token **token, t_data *data)
{
	char	***array;

	array = data->prompt->cmdset;
	array = converttokentosplit(token);
	if (!array || !*array)
		return (1);
	print_array(array);
	(void)clean_array(array);
	return (0);	
}
