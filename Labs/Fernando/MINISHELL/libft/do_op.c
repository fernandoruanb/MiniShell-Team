/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:44:05 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/18 12:02:48 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	do_op(const char *n1, const char operator, const char *n2);

int	main(int argc, char **argv)
{
	int	result;

	if (argc < 4)
	{
		write(1, "\n", 1);
		return (1);
	}
	result = do_op(argv[1], argv[2][0], argv[3]);
	ft_printf("%d\n", result);
	return (0);
}*/

int	do_op(const char *n1, const char operator, const char *n2)
{
	int	result;

	result = 0;
	if (operator == '+')
		result = ft_atoi(n1) + ft_atoi(n2);
	else if (operator == '-')
		result = ft_atoi(n1) - ft_atoi(n2);
	else if (operator == '*')
		result = ft_atoi(n1) * ft_atoi(n2);
	else if (operator == '/')
	{
		if (ft_atoi(n2) == 0)
			return (0);
		result = ft_atoi(n1) / ft_atoi(n2);
	}
	else if (operator == '%')
	{
		if (ft_atoi(n2) == 0)
			return (0);
		result = ft_atoi(n1) % ft_atoi(n2);
	}
	return (result);
}
