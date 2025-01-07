/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:22:37 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/20 16:22:37 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdlib.h>
#include <stdio.h>*/

/*void	ft_lstclear(t_list **lst, void (*del)(void *));

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*new_node2;
	char	*content;
	char	*content2;
	char	*content3;

	if (argc < 4)
		return (1);
	content = argv[1];
	content2 = argv[2];
	content3 = argv[3];
	head = ft_lstnew(content);
	new_node = ft_lstnew(content2);
	new_node2 = ft_lstnew(content3);
	head->next = new_node;
	new_node->next = new_node2;
	new_node2->next = NULL;
	printf("O conteúdo do primeiro nó: %s.\n", (char *)head->content);
	printf("Conteúdo do segundo nó: %s.\n", (char *)new_node->content);
	printf("O conteúdo do terceiro nó: %s.\n", (char *)new_node2->content);
	ft_lstclear(&head, NULL);
	if (!head)
		printf("A lista foi completamente apagada.\n");
	else
		printf("Erro ao deletar a lista.\n");
	return (0);
}*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*add_next;

	if (lst)
	{
		temp = *lst;
		while (temp)
		{
			add_next = temp->next;
			ft_lstdelone(temp, del);
			temp = add_next;
		}
		*lst = NULL;
	}
}
