/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:13:58 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/23 15:27:29 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
//#include <stdio.h>

/*t_list	*ft_lstnew(void *content);

void	print_elements(void *data);

void	ft_list_foreach(t_list *begin_list, void (*f)(void *));

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*new_node2;

	head = ft_lstnew(argv[1]);
	new_node = ft_lstnew(argv[2]);
	new_node2 = ft_lstnew(argv[3]);
	head->next = new_node;
	new_node->next = new_node2;
	ft_list_foreach(head, print_elements);
	return (0);
}*/

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	while (begin_list)
	{
		(*f)(begin_list->data);
		begin_list = begin_list->next;
	}
}

/*void	print_elements(void *data)
{
	printf("%s\n", (char *)data);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->data = content;
	new_node->next = NULL;
	return (new_node);
}*/
