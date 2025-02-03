/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5-echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:01:12 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/28 15:06:06 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_quotes(char *cmd)
{
	int	single_cnt;
	int	double_cnt;
	int	i;

	i = 0;
	single_cnt = 0;
	double_cnt = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			single_cnt++;
		if (cmd[i] == '\"')
			double_cnt++;
		i++;
	}
	return ((single_cnt % 2 == 0) || (double_cnt % 2 == 0));
}

static void	clear_quotes_aux(t_prompt *prompt, char *quote, int *i, int *j)
{
	int		k;
	int		l;
	char	*dup;
	int		len;

	len = ft_strlen(prompt->input) - 2;
	dup = ft_calloc(len + 1, 1);
	if (!dup)
		return ;
	k = 0;
	l = 0;
	while(prompt->input[k])
	{
		if ((k == *i || k == *j) && prompt->input[k] == *quote)
		{
			k++;
			continue ;
		}
		else
			dup[l++] = prompt->input[k++];
	}
	free(prompt->input);
	prompt->input = dup;
	*i = 0;
	*j = ft_strlen(prompt->input) - 1;
	*quote = '\0';
}

static void	clear_quotes(t_prompt *prompt)
{
	char	quote;
	int		i;
	int		j;

	quote = '\0';
	if (!prompt->input)
		return ;
	i = 0;
	j = ft_strlen(prompt->input) - 1;
	while (i < j)
	{
		if (!quote && (prompt->input[i] == '\'' || prompt->input[i] == '\"'))
			quote = prompt->input[i];
		if (quote && prompt->input[j] == quote)
			clear_quotes_aux(prompt, &quote, &i, &j);
		if (!quote)
			i++;
		else
			j--;
	}
}

static void	print_echo(t_prompt *prompt)
{
	printf("%s\n", prompt->input + 5);
}

void	ft_echo(t_prompt *prompt)
{

	char	*tmp;

	if (!prompt->input)
		return ;
	tmp = enviroment_var(prompt->input, prompt->exit_status);
	if (tmp)
	{
		free(prompt->input);
		prompt->input = ft_strdup(tmp);
		free(tmp);
	}
	if (find_quotes(prompt->input))
	{
		clear_quotes(prompt);
		if (!prompt->input)
			return ;
		return (print_echo(prompt));
	}
	child(prompt);
}
