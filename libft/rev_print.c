/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:00:52 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/16 23:00:52 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*rev_print(char *str);

int	main(int argc, char **argv)
{
	char	*result;

	result = rev_print(argv[1]);
	ft_printf("\nString original: %s\n", result);
	return (0);
}*/

char	*rev_print(char *str)
{
	size_t	length;

	if (!str)
		return (NULL);
	length = ft_strlen(str);
	while (length--)
		write(1, &str[length], 1);
	return (str);
}
