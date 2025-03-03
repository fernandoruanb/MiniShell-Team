/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopereir <jopereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:21:40 by jopereir          #+#    #+#             */
/*   Updated: 2025/03/02 20:59:21 by fruan-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	OBS: env[i] + 5 is for ignore "PATH=" before the paths
*/
// static	char	*find_path(char *cmd, char **env)
// {
// 	int		i;
// 	char	**paths;
// 	char	*path;

// 	if (!cmd)
// 		return (NULL);
// 	i = 0;
// 	while (!ft_strnstr(env[i], "PATH", 4))
// 		i++;
// 	paths = ft_split(env[i] + 5, ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
// 		if (access(path, F_OK | X_OK) == 0)
// 		{
// 			clear_split(paths);
// 			return (path);
// 		}
// 		free(path);
// 		i++;
// 	}
// 	clear_split(paths);
// 	return (NULL);
// }

// static void	execute_proccess(t_prompt *prompt)
// {
// 	if (execve(prompt->path, prompt->cmdset, prompt->envp) == -1)
// 		exit(1);
// }

// int	child(t_prompt *prompt)
// {
// 	prompt->cmdset = ft_split(prompt->input, ' ');
// 	prompt->path = find_path(prompt->cmdset[0], prompt->envp);
// 	if (!prompt->path)
// 		return (1);
// 	prompt->pid = fork();
// 	if (prompt->pid < 0)
// 		return (1);
// 	if (prompt->pid == 0)
// 		execute_proccess(prompt);
// 	waitpid(prompt->pid, &prompt->exit_status, 0);
// 	return (0);
// }

// static int	luke_i_am_your_father(t_prompt *prompt)
// {
// 	char	**pipes;
// 	int		i;

// 	pipes = ft_split(prompt->input, '|');
// 	if (!pipes)
// 		return (1);
// 	free(prompt->input);
// 	i = 0;
// 	while (pipes[i])
// 	{
// 		prompt->input = ft_strdup(pipes[i]);
// 		free(prompt->input);
// 		if (child(prompt))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	aplly_parser(t_token **token, t_data *data)
{
	t_token	*temp;

	temp = *token;
	while (temp)
	{
		parser(&temp, data);
		temp = temp->next;
	}
}

void	analysis(t_data *data)
{
	data->token = lexer(data->prompt->input, data->prompt->envp);
	// data->prompt->exit_status = 2 * !data->token;
	//printf("\033[31mLexer exit:\033[0m %d\n", data->prompt->exit_status);
	if (!data->token)
	{
		data->prompt->exit_status = 2;
		return ;
	}
	init_utils(&data->utils);
	if (check_syntax(data->token, data->prompt->envp, &data->utils))
	{
		data->utils.exit_status = 0;
		data->prompt->exit_status = 0;
		ft_printf(GREEN"OK\n"RESET);
	}
	else
	{
		data->prompt->exit_status = data->utils.exit_status;
		ft_printf("\033[31mExit code:\033[0m %d\n", data->utils.exit_status);
		ft_printf("\033[38;5;214mKO\033[0m\n");
	}
	printf("\033[31mSyntax exit:\033[0m %d\n", data->prompt->exit_status);

	aplly_parser(&data->token, data);
	//my_tree_my_life(data->token, &data->utils);
	//data->prompt->cmdset = converttokentosplit(&data->token);
	token_print(data->token);
	//print_array(data->prompt->cmdset);
	//minishell(data);
	token_clean(data->token);
	clean_program(&data->utils);
	data->prompt->exit_status = data->utils.exit_status;
}
 
// void	exec_cmd(t_prompt *prompt)
// {
// 	// if (ft_strchr(prompt->input, '|'))
// 	// 	if (luke_i_am_your_father(prompt))
// 	// 		return ;

// 	if (ft_strncmp(prompt->input, "cd", 2) == 0)
// 		ft_cd(prompt->input);
// 	if (ft_strncmp(prompt->input, "echo", 4) == 0)
// 		return (ft_echo(prompt));
// 	if (prompt->input != NULL)
// 		child(prompt);
// }


