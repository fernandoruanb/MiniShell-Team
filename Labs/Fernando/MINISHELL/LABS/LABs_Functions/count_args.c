/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:21:36 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/26 12:00:49 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_args(char **argv)
{
	int	params;

	if (!argv)
		return (0);
	params = 1;
	while (argv[params])
		params++;
	return (params);
}
