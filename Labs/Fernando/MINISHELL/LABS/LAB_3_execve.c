/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LAB_3_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:17:30 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/27 12:18:34 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	execve(argv[1], argv + 1, NULL);
	return (0);
}
