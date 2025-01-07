/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:30:11 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/23 08:56:08 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

/*static void	*duplicate_content(void *content);

static void	del_content(void *content);*/

/*t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int	main(int argc, char **argv)
{
	t_list	*head;
	t_list	*new_node;
	t_list	*new_node2;
	t_list	*new_lst;
	t_list	*new_list_content;

	if (argc < 4)
		return (1);
	head = ft_lstnew(argv[1]);
	new_node = ft_lstnew(argv[2]);
	new_node2 = ft_lstnew(argv[3]);
	new_lst = NULL;
	head->next = new_node;
	new_node->next = new_node2;
	new_lst = ft_lstmap(head, duplicate_content, del_content);
	new_list_content = new_lst;
	while (new_list_content)
	{
		printf("Conteúdo do novo nó: %s.\n", (char *)new_list_content->content);
		new_list_content=new_list_content->next;
	}
	return (0);
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

/*static void	del_content(void *content)
{
	free(content);
}

static void	*duplicate_content(void *content)
{
	void	*new_content;

	new_content = content;
	return (new_content);
}*/
