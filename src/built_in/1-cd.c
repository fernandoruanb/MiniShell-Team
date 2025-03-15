/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:59:36 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/15 15:54:49 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*transform_string(char *input, int *flag)
{
	char	*home;
	char	*transformation;
	size_t	len_s1;
	size_t	len_s2;

	home = getenv("HOME");
	len_s1 = ft_strlen(home);
	len_s2 = ft_strlen(input);
	transformation = ft_strjoin(home, input + 1);
	if (!transformation)
		return (NULL);
	*flag = 1;
	return (transformation);
}

static char	*locate_target(char *divine_eye)
{
	int		index;
	int		pass;
	char	*str;

	index = 0;
	pass = 0;
	while (divine_eye[index + 1] != '\0')
	{
		if (divine_eye[index] == 'c'
			&& divine_eye[index + 1] == 'd')
			pass = index;
		index++;
	}
	index = 0;
	while (divine_eye[pass + index] != '\0' && divine_eye[pass + index] != '|')
		index++;
	str = ft_substr(divine_eye, pass, pass + index);
	if (!str)
		return (NULL);
	return (str);
}

static int	check_too_many_arguments(char *divine_eye)
{
	int		index;
	char	*str;

	str = locate_target(divine_eye);
	if (!str)
		return (0);
	if (ft_strcmp(str, "cd") == 0)
	{
		free(str);
		return (0);
	}
	index = 3;
	while (str[index] != '\0')
	{
		if (str[index] == ' '
			|| str[index] == '\t')
		{
			free(str);
			return (1);
		}
		index++;
	}
	free(str);
	return (0);
}

void	ft_cd(char *input)
{
	t_data	*official;
	int		flag;

	official = get_minishell();
	if (check_too_many_arguments(official->prompt->input))
	{
		official->utils.exec_status = 1;
		ft_printf("minishell: cd: too many arguments.\n");
		return ;
	}
	flag = 0;
	if (input == NULL)
		official->utils.line = getenv("HOME");
	else if (ft_strnstr(input, "~", 1))
		official->utils.line = transform_string(input, &flag);
	else if (input && flag != 1)
		official->utils.line = input;
	if (chdir(official->utils.line) == -1)
		official->utils.exec_status = 1;
	else
		official->utils.exec_status = 0;
	if (flag == 1)
		free(official->utils.line);
}
