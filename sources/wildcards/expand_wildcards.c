/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:07:12 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 17:14:46 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_par_tok(t_split **current, int *in_par)
{
	if ((*current)->tok_type == PAR_OPEN)
		*in_par += 1;
	else
		*in_par -= 1;
	*current = (*current)->next;
}

static int	process_wild_n_empty(t_split **current, char **file_list,
		t_split **first)
{
	t_split	*tmp;

	tmp = (*current)->next;
	if (has_wildcard((*current)->str))
	{
		if (expand_one_wildcard(current, file_list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		remove_from_list(first, *current);
		free((*current)->str);
		free(*current);
	}
	*current = tmp;
	return (EXIT_SUCCESS);
}

static void	process_other(t_split **current, int in_par)
{
	if (!in_par)
		quote_trimmer((*current)->str);
	*current = (*current)->next;
}

int	expand_token_list(t_split **first, char **file_list)
{
	t_split	*current;
	int		in_par;

	in_par = 0;
	current = *first;
	if (!file_list)
		return (EXIT_SUCCESS);
	while (current)
	{
		if (current->sub_tok_type == PAR)
			process_par_tok(&current, &in_par);
		else if (current->sub_tok_type == REDIR)
			current = current->next->next;
		else if (!in_par && (has_wildcard(current->str) || !current->str[0]))
		{
			if (process_wild_n_empty(&current, file_list,
					first) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
			process_other(&current, in_par);
	}
	return (EXIT_SUCCESS);
}
