/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:03:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/01/21 11:17:14 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	int	id;

	printf("I'm the father process and my PID is: %d\n", getpid());
	id = fork();
	printf("Do you now who am I? %d\n", id);
	if (id == 0)
		printf("I'm the child. My father is the main process.\n");
	else
		printf("Child. I'm your father.\n");
	printf("Hello from processes!!!\n");
	return (0);
}
