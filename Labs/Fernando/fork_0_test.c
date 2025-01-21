/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:06:17 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 12:11:59 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	id;

	id = fork();
	if (id == 0)
		printf("I'm the child process. My ID is %d and \
my PID is %d\n", id, getpid());
	else
		printf("I'm the father process. My ID is %d and \
my PID is %d\n", id, getpid());
	return (0);
}
