/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultimate_ft_strlen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:18:41 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/17 10:29:43 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*size_t	ultimate_ft_strlen(const char *s1, const char *s2, const char *s3);

int	main(int argc, char **argv)
{
	size_t	result;

	if (argc < 4)
		return (1);
	result = ultimate_ft_strlen(argv[1], argv[2], argv[3]);
	ft_printf("%d\n", result);
	return (0);
}*/

size_t	ultimate_ft_strlen(const char *s1, const char *s2, const char *s3)
{
	size_t	len_total;
	size_t	temp;

	len_total = 0;
	temp = 0;
	if (s1)
	{
		while (s1[len_total] != '\0')
			len_total++;
	}
	if (s2)
	{
		while (s2[temp] != '\0')
			temp++;
	}
	len_total += temp;
	temp = 0;
	if (s3)
	{
		while (s3[temp] != '\0')
			temp++;
	}
	len_total += temp;
	return (len_total);
}
