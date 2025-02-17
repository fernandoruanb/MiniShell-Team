/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:50:50 by fruan-ba          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/17 12:30:16 by jopereir         ###   ########.fr       */
=======
/*   Updated: 2025/02/17 12:41:38 by fruan-ba         ###   ########.fr       */
>>>>>>> f3e62c3120b058ffc9dd0fc740ff5e785a918367
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	correct_index(t_token *root, int *index, char *quote)
{
	if (root->str[0] == '\\')
		*index += 2;
	if (*index == 2)
		return (1);
	if (root->str[0] == '\'' || root->str[0] == '\"')
	{
		*quote = root->str[0];
		*index = 1;
		while (root->str[*index] != '\0' && root->str[*index] != *quote)
		{
			if (root->str[*index] == '\\')
				(*index)++;
			(*index)++;
		}
		if (root->str[*index] == '\0')
			return (0);
	}
	else
		*index = 1;
	if (root->str[*index] == '\'' || root->str[*index] == '\"')
		(*index)++;
	return (1);
}

int	check_final_quotes(t_token *root)
{
	int		index;
	char	quote;

<<<<<<< HEAD
	index = -1;
	if (root->str[0] == '\\')
		index += 2;
	while (root->str[++index] != '\0')
=======
	index = 0;
	if (!correct_index(root, &index, &quote))
		return (0);
	while (root->str[index] != '\0')
>>>>>>> f3e62c3120b058ffc9dd0fc740ff5e785a918367
	{
		if ((root->str[index + 1] && root->str[index] != '\\') && (root->str[index + 1] == '\''
			|| root->str[index] == '\"'))
		{
			quote = root->str[index];
			index++;
			while (root->str[index] != '\0' && root->str[index] != quote)
			{
				if (root->str[index] == '\\')
					index++;
				index++;
			}
			if (root->str[index] == '\0')
				return (0);
		}
	}
	return (1);
}

static int	check_quotes_cmd_special_case(t_token *root)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = ft_strlen(root->str);
	if ((root->str[0] == '\'' || root->str[0] == '\"')
		&& (root->str[length - 1] == '\''
			|| root->str[length - 1] == '\"'))
	{
		while (root->str[index] != '\0')
		{
			if (root->str[index] == ' '
				|| root->str[index] == '\t')
				return (1);
			index++;
		}
	}
	return (0);
}

int	how_many_quotes(t_token *root, t_utils *data)
{
	if (root->id == CMD && check_quotes_cmd_special_case(root))
		return (0);
	if ((root->id == CMD || root->id == ARG)
		&& check_final_quotes(root))
		return (1);
	else if ((root->id == CMD || root->id == ARG) && !check_final_quotes(root))
		return (0);
	if (data->simple_quotes % 2 != 0 || data->double_quotes % 2 != 0)
		return (show_error_fd("Syntax: QUOTES Error", 0, data, 0));
	return (0);
}
