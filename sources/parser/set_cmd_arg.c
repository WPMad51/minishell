/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:06:25 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 22:30:37 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_tok_is_cmd(t_split **current, t_cmd *output, t_heredocs **heredocs,
		int *length)
{
	if ((*current)->tok_type == HD)
		output->hd_rolls++;
	if (add_file_list(&output->files, *current, heredocs,
			length) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*current = (*current)->next;
	return (EXIT_SUCCESS);
}

int	write_current_arg(t_cmd *output, t_split *current, int *index)
{
	output->args[*index] = ft_strdup(current->str);
	if (output->args[*index] == NULL)
		return (EXIT_FAILURE);
	*index += 1;
	return (EXIT_SUCCESS);
}

int	get_files_n_args(t_split *current, int length, t_cmd *output,
		t_heredocs **heredocs)
{
	int	in_par;
	int	index;

	index = 0;
	in_par = 0;
	while (current && --length)
	{
		if (current->sub_tok_type == PAR)
			process_in_par(current->tok_type, &in_par);
		else if (!in_par && current->tok_type != CMD)
		{
			if (process_tok_is_cmd(&current, output, heredocs,
					&length) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (!in_par && write_current_arg(output, current,
				&index) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	set_cmd_arg(t_cmd *output, t_split *first, int length,
		t_heredocs **heredocs)
{
	t_split	*current;

	current = first;
	if (alloc_output_args(&output->args, first, length - 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!output->args && update_heredocs(current, length, output, heredocs)
		&& copy_list(&output->copy, first) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (get_files_n_args(current, length, output, heredocs) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	update_heredocs(t_split *current, int length, t_cmd *output,
		t_heredocs **heredocs)
{
	int	in_par;

	in_par = 0;
	while (current && --length)
	{
		if (current->sub_tok_type == PAR)
			process_in_par(current->tok_type, &in_par);
		else if (in_par && current->tok_type == HD)
		{
			output->hd_rolls++;
			get_first_heredoc(heredocs);
		}
		current = current->next;
	}
	return (1);
}
