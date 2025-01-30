/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snake_to_camel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:11:13 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/20 19:31:33 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*void	snake_to_camel(char *s);

int	main(int argc, char **argv)
{
	(void)argc;
	snake_to_camel(argv[1]);
	write(1, "\n", 1);
	return (0);
}*/

void	snake_to_camel(char *s)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (index != 0 && s[index - 1] == '_')
		{
			if (s[index] >= 'a' && s[index] <= 'z')
				s[index] = s[index] - 32;
			write(1, &s[index], 1);
		}
		else if (s[index] != '_')
			write(1, &s[index], 1);
		index++;
	}
}
