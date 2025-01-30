/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:48:06 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/30 10:43:05 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


char	*ft_strdup(const char *s)
{
	char	*buffer;
	int		length;
	int		index;

	index = 0;
	length = strlen(s);
	buffer = (char *)malloc(length + 1);
	if (!buffer)
		return (NULL);
	while (s[index] != '\0')
	{
		buffer[index] = s[index];
		index++;
	}
	buffer[index] = '\0';
	return (buffer);
}

typedef struct s_token
{
	char	**argv;
	int		argc;
}	t_token;


int	main(void){
	char	*cmd;

	cmd = ft_strdup("ls -l | wc -l");
	return (0);
}
