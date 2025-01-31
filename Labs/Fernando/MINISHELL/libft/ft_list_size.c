/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:38:43 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/11/22 12:49:41 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	ft_list_size(t_list *begin_list);

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*new_node2;
	int	result;

	head = ft_lstnew(argv[1]);
	new_node = ft_lstnew(argv[2]);
	new_node2 = ft_lstnew(argv[3]);
	head->next = new_node;
	new_node->next = new_node2;
	result = ft_list_size(head);
	ft_printf("%d\n", result);
	return (0);
}*/

int	ft_list_size(t_list *begin_list)
{
	int	count;

	if (!begin_list)
		return (0);
	count = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		count++;
	}
	return (count);
}
