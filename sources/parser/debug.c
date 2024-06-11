/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 08:00:35 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 15:07:22 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// void	print_list(t_split *first)
// {
// 	t_split	*current;

// 	if (first == NULL)
// 		return ;
// 	current = first;
// 	while (current)
// 	{
// 		printf("'%s'\n", current->str);
// 		current = current->next;
// 	}
// }

// void	print_args(char **args)
// {
// 	int	i;

// 	i = 0;
// 	if (!args)
// 		printf("none\n");
// 	else
// 	{
// 		while (args[i])
// 		{
// 			printf("args[%d] => %s\n", i, args[i]);
// 			i++;
// 		}
// 	}
// }

// void	print_files(t_file *files)
// {
// 	t_file	*current;

// 	current = files;
// 	if (!current)
// 		printf("none\n");
// 	else
// 	{
// 		while (current)
// 		{
// 			printf("file type : %d, file name or limiter : %s\n",
// 				current->redir_type,
// 				current->file_name ? current->file_name : current->limiter);
// 			current = current->next;
// 		}
// 	}
// }

// void	print_commands(t_cmd *first)
// {
// 	t_cmd	*current;

// 	current = first;
// 	while (current)
// 	{
// 		printf("================\n");
// 		printf("    ARGS\n");
// 		if (current->args[0])
// 			print_args(current->args);
// 		else
// 			printf("NO ARGS\n");
// 		printf("    FILES\n");
// 		print_files(current->files);
// 		printf("================\n");
// 		current = current->next;
// 	}
// }

// void	print_tree(t_node *tree_top, t_mini *mini, char **files,
// 		t_heredocs **heredocs)
// {

// 	if (tree_top == NULL)
// 		return ;
// 	print_tree(tree_top->left, mini, files, heredocs);
// 	expand_node(tree_top, mini, files, heredocs);
// 	printf("==============node start%d\n", tree_top->node_type);
// 	print_list(tree_top->first_token);
// 	printf("COMMANDS\n");
// 	if (tree_top->cmds == NULL)
// 		printf("none\n");
// 	else
// 		print_commands(tree_top->cmds);
// 	printf("==============node end\n");
// 	print_tree(tree_top->right, mini, files, heredocs);
// }
