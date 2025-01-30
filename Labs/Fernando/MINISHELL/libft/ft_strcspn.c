/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:59:42 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/18 15:16:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <string.h>*/

/*size_t	ft_strcspn(const char *s, const char *reject);

int	main(int argc, char **argv)
{
	size_t	length;
	size_t	length_2;

	if (argc < 3)
		return (1);
	length = ft_strcspn(argv[1], argv[2]);
	length_2 = strcspn(argv[1], argv[2]);
	printf("(MY FUNCTION): %zu\n", length);
	printf("(ORIGINAL): %zu\n", length_2);
	return (0);
}*/

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = 0;
	while (s[index] != '\0' && !ft_strchr(reject, s[index]))
	{
		index++;
		length++;
	}
	return (length);
}
