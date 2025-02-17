/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-tokensort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:37:47 by jopereir          #+#    #+#             */
/*   Updated: 2025/02/17 17:48:36 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token **token)
{
	char	***array;

	array = converttokentosplit(token);
	print_array(array);
	clean_array(array);
	return (0);	
}
