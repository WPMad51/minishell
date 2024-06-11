/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:56:06 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 16:48:04 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_parenthesis(t_node *node)
{
	t_split	*current;
	t_split	*tmp;

	tmp = node->first_token;
	node->first_token = node->first_token->next;
	destroy_split(tmp);
	current = node->first_token;
	while (current->next)
	{
		tmp = current;
		current = current->next;
	}
	current = tmp->next;
	destroy_split(current);
	tmp->next = NULL;
	node->node_type = get_node_type(node->first_token);
}

int	split_comb_node(t_node *current)
{
	t_split	*tmp;

	tmp = get_last_tok(&current->first_token);
	current->right = create_new_node(tmp, get_node_type(tmp));
	if (!current->right)
		return (destroy_split_list(&tmp, EXIT_FAILURE));
	tmp = get_last_tok(&current->first_token);
	current->left = create_new_node(current->first_token,
			get_node_type(current->first_token));
	if (!current->left)
		return (destroy_split_list(&tmp, EXIT_FAILURE));
	current->first_token = tmp;
	current->node_type = get_node_type(current->first_token);
	return (EXIT_SUCCESS);
}

int	decomp_node(t_node *current)
{
	if (current == NULL)
		return (EXIT_SUCCESS);
	if (current->node_type == COMB && split_comb_node(current) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (current->node_type == CMD || current->node_type == PAR)
		return (EXIT_SUCCESS);
	if (decomp_node(current->left) == EXIT_FAILURE
		|| decomp_node(current->right) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_split	*get_last_tok(t_split **first)
{
	int		in_par;
	t_split	*current;
	t_split	*last_eoc;
	t_split	*output;

	current = *first;
	last_eoc = current;
	in_par = 0;
	while (current)
	{
		if (current->tok_type == PAR_OPEN)
			in_par++;
		else if (current->tok_type == PAR_CLOSE)
			in_par--;
		else if ((current->tok_type == AND || current->tok_type == OR)
			&& !in_par)
			last_eoc = current;
		current = current->next;
	}
	output = last_eoc->next;
	last_eoc->next = NULL;
	if (output)
		return (output);
	else
		return (remove_from_list(first, last_eoc), last_eoc);
}

int	destroy_tree(t_node **tree_top, int value)
{
	t_node	*tree_current;

	tree_current = *tree_top;
	if (tree_current == NULL)
		return (value);
	destroy_tree(&tree_current->left, value);
	destroy_tree(&tree_current->right, value);
	if (tree_current->cmds)
		destroy_cmds_list(&tree_current->cmds, value);
	if (tree_current->first_token)
		destroy_split_list(&tree_current->first_token, value);
	free(tree_current);
	*tree_top = NULL;
	return (value);
}
