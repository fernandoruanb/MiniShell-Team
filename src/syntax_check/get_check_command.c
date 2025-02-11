/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_check_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 08:42:15 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/02/11 17:12:02 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_check_command(t_token *root, t_utils *data)
{
	char	buffer[4096];
	int		index;
	int		count;

	index = 0;
	count = 0;
	while (root->str[index] != '\0')
	{
		if (ft_isalpha_special_2(root->str[index]))
		{
			buffer[count] = root->str[index];
			count++;
		}
		index++;
	}
	buffer[count] = '\0';
	printf("BUFFER: %s\n", buffer);
	check_copy_new(data);
	data->copy_new = ft_strdup(buffer);
	if (!data->copy_new)
		return (0);
	if (!final_check(data))
		return (0);
	return (1);
}
