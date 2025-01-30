/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:34:19 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/20 15:34:19 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

/*void	ft_lstadd_front(t_list **lst, t_list *new);

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;

	if (argc < 3)
		return (1);
	head = ft_lstnew(argv[1]);
	new_node = ft_lstnew(argv[2]);
	ft_lstadd_front(&head, new_node);
	printf("O primeiro nó é: %s.\n", (char *)head->content);
	printf("O segundo nó é: %s.\n", (char *)head->next->content);
	free(head);
	return (0);
}*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
