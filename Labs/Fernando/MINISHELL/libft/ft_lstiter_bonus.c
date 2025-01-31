/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:26:06 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/20 16:26:06 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

/*static void	show_content(void *content);

void	ft_lstiter(t_list *lst, void (*f)(void *));

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*new_node2;

	if (argc < 4)
		return (1);
	head = ft_lstnew(argv[1]);
	new_node = ft_lstnew(argv[2]);
	new_node2 = ft_lstnew(argv[3]);
	head->next = new_node;
	new_node->next = new_node2;
	ft_lstiter(head, show_content);
	return (0);
}*/

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst)
	{
		while (lst)
		{
			(*f)(lst->content);
			lst = lst->next;
		}
	}
}

/*static void	show_content(void *content)
{
	printf("O conteúdo do meu nó é: %s.\n", (char *)content);
}*/
