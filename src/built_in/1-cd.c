/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:24:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/24 15:22:41 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(char *input)
{
	chdir(&input[3]);
}
