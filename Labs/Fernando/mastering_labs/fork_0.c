/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:31:09 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 12:37:13 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	id;

	id = fork();
	if (id == 0)
		printf("I'm the child process and my \
ID and PID are %d and %d\n", id, getpid());
	if (id != 0)
		printf("I'm the father process and m \
ID and PID are %d and %d\n", id, getpid());
	return (0);
}
