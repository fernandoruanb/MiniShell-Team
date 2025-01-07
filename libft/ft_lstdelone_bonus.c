/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdealone_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:19:26 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/20 16:19:26 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

//void	del_content(void *content);

/*void	ft_lstdelone(t_list *lst, void (*del)(void *));

int	main(int argc, char **argv)
{
	t_list	*new_node;
	char	*content;

	if (argc < 2)
		return (1);
	content = ft_strdup(argv[1]);
	new_node = ft_lstnew(content);
	printf("O nó antes de deletar: %s.\n", (char *)new_node->content);
	ft_lstdelone(new_node, del_content);
	printf("O nó morreu!!!\n");
	return (0);
}*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*void	del_content(void *content)
{
	free(content);
}*/
