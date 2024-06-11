/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_parsing_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:07:29 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 20:49:55 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_new_cmd(t_split *first, int length, t_heredocs **heredocs)
{
	t_cmd	*output;

	output = malloc(sizeof(t_cmd));
	if (!output)
		return (NULL);
	ft_bzero(output, sizeof(t_cmd));
	if (set_cmd_arg(output, first, length + 1, heredocs) == EXIT_FAILURE)
	{
		destroy_file_list(&output->files);
		destroy_tab(&output->args);
		free(output);
		return (NULL);
	}
	return (output);
}

void	process_in_par(t_tok_type type, int *in_par)
{
	if (type == PAR_CLOSE)
		*in_par -= 1;
	else
		*in_par += 1;
}

int	addback_cmds_list(t_cmd **start, t_split *first_token, int length,
		t_heredocs **heredocs)
{
	t_cmd	*current;
	t_cmd	*new;

	new = create_new_cmd(first_token, length, heredocs);
	if (!new)
		return (EXIT_FAILURE);
	if (*start == NULL)
	{
		*start = new;
		return (EXIT_SUCCESS);
	}
	current = *start;
	while (current->next)
		current = current->next;
	current->next = new;
	return (EXIT_SUCCESS);
}

t_split	*copy_split_elem(t_split *current)
{
	t_split	*new;

	new = malloc(sizeof(t_split));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_split));
	new->str = ft_strdup(current->str);
	if (!new->str)
		return (free(new), NULL);
	new->sub_tok_type = current->sub_tok_type;
	new->tok_type = current->tok_type;
	return (new);
}
