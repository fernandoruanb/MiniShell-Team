/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:25:21 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/21 17:12:09 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <string.h>

void	*ft_free(void *a, void *b)
{
	free(a);
	free(b);
	return (NULL);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
	Concatena uma str com um caractere
*/
static char	*ft_strchar(char *str, char c)
{
	char	*s;
	int		len;
	int		i;

	len = ft_strlen(str) + 2;
	s = calloc(len, 1);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i++] = c;
	s[i] = '\0';
	return (s);
}

char	*first_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (&str[++i]);
		i++;
	}
	return (NULL);
}

char	*display_prompt(void)
{
	char	*dir_path;
	char	*prompt;
	int		len;

	len = 1024;
	dir_path = calloc(len, 1);
	if (!dir_path)
		return (NULL);
	if (getcwd(dir_path, len))
	{
		prompt = ft_strchar(first_char(strstr(dir_path, "home"), '/'), ' ');
		if (!prompt)
			return (ft_free(dir_path, NULL));
		return (prompt);
	}
	return (NULL);
}

/*
	compilar com a flag -lreadline -lncurses
*/
void	get_input(void)
{
	char	*input;
	char	*dir_path;

	while (1)
	{
		dir_path = display_prompt();
		input = readline(dir_path);
		if (!input)
		{
			printf("\n");
			ft_free(dir_path, input);
			rl_clear_history();
			break ;
		}
		if (input)
			add_history(input);
		printf("O seu input foi: %s\n", input);
		ft_free(dir_path, input);
	}
}

int	main(void)
{
	get_input();
	return (0);
}
