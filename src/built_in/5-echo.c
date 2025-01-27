/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:01:12 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/27 15:21:10 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_quotes_couples(char *cmd)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			cnt++;
		i++;
	}
	return (cnt >= 2);
}

static int	get_len(char *cmd)
{
	int	i;
	int	len;

	len = ft_strlen(cmd);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
			len--;
		i++;
	}
	return (len);
}

// static char	*cpy_without_quotes(char *cmd)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*cpy;

// 	len = get_len(cmd);
// 	cpy = ft_calloc(len + 1, 1);
// 	if (!cpy)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] != '\'' && cmd[i] != '\"')
// 			cpy[j++] = cmd[i];
// 		i++;
// 	}
// 	cpy[len] = '\0';
// 	return (cpy);
// }

static char	*cpy_without_quotes(char *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*cpy;

	len = get_len(cmd);
	cpy = ft_calloc(len + 1, 1);
	if (!cpy)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] != '\'' && cmd[i] != '\"')
			cpy[j++] = cmd[i];
		i++;
	}
	cpy[len] = '\0';
	return (cpy);
}

static void	clear_quotes(t_prompt *prompt, int index)
{
	char	*temp;

	temp = ft_strdup(prompt->cmdset[index]);
	if (!temp)
		return ;
	free(prompt->cmdset[index]);
	prompt->cmdset[index] = cpy_without_quotes(temp);
	free(temp);
}

void	ft_echo(t_prompt *prompt)
{
	int		i;
	char	*tmp;
	int		quotes;

	i = 1;
	while (prompt->cmdset[i])
	{
		tmp = enviroment_var(prompt->cmdset[i], prompt->exit_status);
		if (tmp)
		{
			free(prompt->cmdset[i]);
			prompt->cmdset[i] = ft_strdup(tmp);
			free(tmp);
		}
		quotes = find_quotes_couples(prompt->cmdset[i]);
		if (quotes)
		{
			clear_quotes(prompt, i);
			if (!prompt->cmdset[i])
				return ;
		}
		quotes = 0;
		i++;
	}
	child(prompt);
}
