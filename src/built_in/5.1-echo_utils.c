/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.1-echo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:58:08 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/27 14:19:47 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_a_cpy(char *cmd, char *dest, char *sign, char *status)
{
	int		i;
	int		j;
	char	*temp;
	int		sign_len;

	i = 0;
	j = 0;
	sign_len = ft_strlen(sign);
	while (cmd[i])
	{
		if (ft_strncmp(&cmd[i], sign, sign_len) == 0)
		{
			while (status[j])
				dest[i++] = status[j++];
			i++;
			temp = ft_strjoin(dest, &cmd[i]);
			return (temp);
		}
		dest[i] = cmd[i];
		i++;
	}
	return (dest);
}

static char	*change_var(char *cmd, char *sign, int status)
{
	char	*temp;
	char	*stat;
	int		len;

	stat = ft_itoa(status);
	if (!stat)
		return (NULL);
	len = ft_strlen(cmd) - ft_strlen(sign) + ft_strlen(stat) + 1;
	temp = ft_calloc(len, 1);
	if (!temp)
	{
		free(stat);
		return (NULL);
	}
	temp = make_a_cpy(cmd, temp, sign, stat);
	free(stat);
	return (temp);
}

char	*enviroment_var(char *cmd, int exit_status)
{
	if (ft_strnstr(cmd, "$?", ft_strlen(cmd)))
		return (change_var(cmd, "$?", exit_status));
	return (NULL);
}
