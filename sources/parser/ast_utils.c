/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 05:32:42 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 15:07:50 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*create_new_node(t_split *first_elem, t_node_type type)
{
	t_node	*output;

	output = malloc(sizeof(t_node));
	if (!output)
		return (NULL);
	ft_bzero(output, sizeof(t_node));
	output->first_token = first_elem;
	output->node_type = type;
	return (output);
}

int	create_tree(t_node **tree_top, t_split **elem)
{
	t_node	*current;

	current = create_new_node(*elem, get_node_type(*elem));
	if (!current)
		return (destroy_split_list(elem, EXIT_FAILURE));
	if (decomp_node(current) == EXIT_FAILURE)
		return (destroy_tree(&current, EXIT_FAILURE));
	*tree_top = current;
	return (EXIT_SUCCESS);
}

void	remove_from_list(t_split **first, t_split *to_remove)
{
	t_split	*current;

	if (!(*first) || !to_remove)
		return ;
	if (*first == to_remove)
	{
		*first = (*first)->next;
		return ;
	}
	current = *first;
	while (current)
	{
		if (current->next == to_remove)
		{
			current->next = to_remove->next;
			return ;
		}
		current = current->next;
	}
}

int	is_only_par(t_split *elem)
{
	int		in_par;
	t_split	*current;

	in_par = 0;
	current = elem;
	if (elem->tok_type != PAR_OPEN)
		return (0);
	while (current->next)
	{
		if (current->tok_type == PAR_OPEN)
			in_par++;
		if (current->tok_type == PAR_CLOSE && in_par == 1)
			break ;
		else if (current->tok_type == PAR_CLOSE)
			in_par--;
		current = current->next;
	}
	if (current->next)
		return (0);
	return (1);
}

t_node_type	get_node_type(t_split *elem)
{
	t_split	*current;
	int		in_par;

	in_par = 0;
	if (elem->tok_type == PAR_OPEN && is_only_par(elem))
		return (CMD);
	if ((elem->tok_type == OR || elem->tok_type == AND) && !elem->next)
		return (elem->tok_type);
	current = elem;
	while (current)
	{
		if (current->tok_type == PAR_OPEN)
			in_par++;
		else if (current->tok_type == PAR_CLOSE)
			in_par--;
		else if (!(current->tok_type == PIPE || current->sub_tok_type == CMD
				|| current->sub_tok_type == REDIR) && !in_par)
			return (COMB);
		current = current->next;
	}
	return (CMD);
}
