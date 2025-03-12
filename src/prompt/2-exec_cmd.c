/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-exec_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:32:28 by fruan-ba          #+#    #+#             */
/*   Updated: 2025/03/12 15:23:55 by jonas            ###   ########.fr       */
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

// void	aplly_parser(t_token **token, t_data *data)
// {
// 	t_token	*temp;

// 	temp = *token;
// 	while (temp)
// 	{
// 		parser(&temp, data);
// 		temp = temp->next;
// 	}
// }

// t_ast	*make_ast(t_token **token)
// {
// 	t_token *temp;
// 	t_ast	*new;

// 	temp = *token;
// 	new = NULL;
// 	while (temp->next)
// 		temp = temp->next;
// 	while (temp->previous)
// 	{
// 		if (temp->id != CMD && temp->id != ARG)
// 			new = add_node(new, &temp);
// 		temp = temp->previous;
// 	}
// 	while (temp)
// 	{
// 		if (temp->id == CMD || temp->id == FD || temp->id == LIMITER)
// 			new = add_node(new, &temp);
// 		temp = temp->next;
// 	}
// 	return (new);
// }

void ast_print(t_ast *root, int level)
{
	if (!root)
		return ;
	ast_print(root->right, level + 1);
	for (int i = 0; i < level; i++)
		printf("     ");
	printf("%s (%d)(%s)\n", root->cmd[0], root->index, root->id == CMD ? "CMD" : root->id == LIMITER ? "LIMITER" : root->id == FD ? "FD" : root->id == PIPE ? "PIPE" : "REDIRECT");
	ast_print(root->left, level + 1);
}

void	clear_everything(t_data *data, int flag)
{
	if (flag)
		clean_node(&data->root);
	token_clean(data->token);
	clear_split(data->envp);
	data->flags.should_clean = false;
	printf("clear_everything\nshound clean alterada: %s\n", data->flags.should_clean ? "true" : "false");
}

void	analysis(t_data *data)
{
	data->envp = updateenvp(&data->export_vars);
	data->token = lexer(data->prompt->input, data->envp);
	if (!data->token)
	{
		data->prompt->exit_status = 2;
		return ;
	}
	token_print(data->token);
	init_utils(&data->utils, data->envp);
	if (!check_syntax(data->token, data->envp, &data->utils))
	{
		data->prompt->exit_status = data->utils.exit_status;
		printf("Syntax: KO\n");
		return (clear_everything(data, 0));
	}
	printf("Syntax: OK\n");
	make_ast(&data->token, &data->root, data);
	data->flags.should_clean = true;
	printf(RED"AST\n"RESET);
	ast_print(data->root, 0);
	print_node(data->root);
	printf("\n");
	printf(GREEN"OUTPUT:"RESET);
	printf("\n");
	minishell(&data->root, data);
	clean_program(&data->utils);
	if (data->flags.should_clean)
		clear_everything(data, 1);
	data->prompt->exit_status = data->utils.exec_status;
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
