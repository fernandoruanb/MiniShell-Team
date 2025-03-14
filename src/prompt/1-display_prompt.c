/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-display_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/13 21:59:57 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\0')
			return (0);
	return (1);
}

void	display_prompt(t_data *data)
{
	while (1)
	{
		data->prompt->input
			= readline(FERNANDO_BLUE"(mini)Universe"RESET_PROMPT);
		if (!data->prompt->input)
			ft_exit(data, NULL);
		data->utils.rl_flag = 1;
		if (handle_space(data->prompt->input))
		{
			free(data->prompt->input);
			continue ;
		}
		if (data->prompt->input[0] != '\0')
		{
			add_history(data->prompt->input);
			analysis(data);
			data->utils.rl_flag = 0;
		}
		free(data->prompt->input);
		data->prompt->input = NULL;
	}
}
