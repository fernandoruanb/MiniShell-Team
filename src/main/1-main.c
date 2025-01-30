/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:09:08 by jopereir          #+#    #+#             */
/*   Updated: 2025/01/30 11:23:54 by jopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT)
		printf("\n\033[1;36m<<Master of universe(mini)>>$ \033[0m");
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;

// 	(void)argv;
// 	signal(SIGINT, handle_signal);
// 	if (argc != 1)
// 		return (1);
// 	create(&data, envp);
// 	return (0);
// }

typedef struct s_token
{
	char			**argv;
	int				argc;

	struct s_token	*next;	
}	t_token;

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '$');
}

char	**get_elements(char *str){
	char	**argv;
	int		i;

		
	return (argv);
}

t_token	*new_token(char *input)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->argv = ft_split(input, ' ');
	new->next = NULL;
	return (new);
}

void	print_argv(char **str){
	int	i, j;

	i = 0;
	while (str[i]){
		j = 0;
		while (str[i][j])
			printf("%c", str[i][j++]);
		printf("\n");
		i++;
	}
}

int	main(void){
	char		*cmd;
	t_token		*tokens;

	signal(SIGINT, handle_signal);
	cmd = ft_strdup("ls -l | wc -l");
	tokens = new_token(cmd);
	print_argv(tokens->argv);
	return (0);
}
