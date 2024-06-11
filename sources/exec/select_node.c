/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:41:57 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 13:34:39 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	select_node(t_node *current, t_mini *mini)
{
	int	exec_res;

	if (!current)
		return (EXIT_SUCCESS);
	if (select_node(current->left, mini) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (current->node_type == CMD && mini->fatal_error != 1)
	{
		exec_res = exec_node(current, mini);
		dup2(mini->save_stdin, STDIN_FILENO);
		dup2(mini->save_stdout, STDOUT_FILENO);
		return (exec_res);
	}
	else if (current->node_type == AND && mini->exit_status == 0
		&& mini->fatal_error != 1)
		return (select_node(current->right, mini));
	else if (current->node_type == OR && mini->exit_status != 0
		&& mini->fatal_error != 1)
		return (select_node(current->right, mini));
	if (mini->fatal_error == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
