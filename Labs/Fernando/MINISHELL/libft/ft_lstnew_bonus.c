/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fruan-ba <fruan-ba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:47:01 by fruan-ba          #+#    #+#             */
/*   Updated: 2024/10/20 16:47:01 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

/*t_list	*ft_lstnew(void *content);

int main(int argc, char **argv)
{
	char	*content;

	if (argc < 2)
		return (1);
	content = argv[1];
	t_list *node = ft_lstnew(content);
	if (node != NULL)
		printf("Conteúdo do nó: %s\n", (char *)node->content);
    	else
		printf("Erro ao criar o nó\n");
	free(node);
	return 0;
}*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list;

	new_list = malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}
