/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:48:47 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/20 15:48:47 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <stdlib.h>*/

/*int	ft_lstsize(t_list *lst);

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*new_node2;
	t_list	*new_node3;
	int	result;

	if (argc < 5)
		return (1);
	head = ft_lstnew(argv[1]);
	new_node = ft_lstnew(argv[2]);
	new_node2 = ft_lstnew(argv[3]);
	new_node3 = ft_lstnew(argv[4]);
	head->next = new_node;
	new_node->next = new_node2;
	new_node2->next = new_node3;
	result = ft_lstsize(head);
	printf("A quantidade de nós existentes é: %i.\n", result);
	free(head);
	return (0);
}*/

int	ft_lstsize(t_list *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}
