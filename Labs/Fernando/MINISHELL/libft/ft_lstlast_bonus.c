/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:17:26 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/20 16:17:26 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>
#include <stdlib.h>

t_list	*ft_lstlast(t_list *lst);

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*new_node2;
	t_list	*new_node3;
	t_list	*result;
	if (argc < 5)
		return (1);
	head = ft_lstnew(argv[1]);
	new_node = ft_lstnew(argv[2]);
	new_node2 = ft_lstnew(argv[3]);
	new_node3 = ft_lstnew(argv[4]);
	head->next = new_node;
	new_node->next = new_node2;
	new_node->next = new_node3;
	new_node3->next = NULL;
	result = ft_lstlast(head);
	printf("O conteúdo do último nó é: %s.\n", (char *)result->content);
	free(head);
	free(new_node);
	free(new_node2);
	free(new_node3);
	return (0);
}*/

t_list	*ft_lstlast(t_list *lst)
{
	if (lst != NULL)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}
