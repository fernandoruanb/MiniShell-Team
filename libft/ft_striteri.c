/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:26:24 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/15 16:26:26 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>

static void	ft_toupper_i(unsigned int index, char *c);

void	ft_striteri(char *s, void (*f)(unsigned int, char *));

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	printf("A string bonita para teste: %s.\n", argv[1]);
	ft_striteri(argv[1], ft_toupper_i);
	printf("(MY FUNCTION) %s.\n", argv[1]);
	return (0);
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	index;

	if (!s || !f)
		return ;
	index = 0;
	while (s[index] != '\0')
	{
		f(index, &s[index]);
		index++;
	}
}

/*static void	ft_toupper_i(unsigned int index, char *c)
{
	if (index % 2 == 0 && (*c >= 'a' && *c <= 'z'))
		*c = *c - ('a' - 'A');
}*/
