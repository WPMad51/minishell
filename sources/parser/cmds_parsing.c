/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:20:52 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 20:50:06 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parse_cmds(t_split *first_token, t_heredocs **heredocs, int i,
		int in_par)
{
	t_split	*current;
	t_split	*tmp;
	t_cmd	*output;

	output = NULL;
	current = first_token;
	tmp = first_token;
	while (current)
	{
		if (current->sub_tok_type == PAR)
			process_in_par(current->tok_type, &in_par);
		else if (!in_par && current->tok_type == PIPE)
		{
			if (addback_cmds_list(&output, tmp, i - 1,
					heredocs) == EXIT_FAILURE)
				return (destroy_cmds_list(&output, EXIT_FAILURE), NULL);
			i = 0;
			tmp = current->next;
		}
		i++;
		current = current->next;
	}
	if (addback_cmds_list(&output, tmp, i - 1, heredocs) == EXIT_FAILURE)
		return (destroy_cmds_list(&output, EXIT_FAILURE), NULL);
	return (output);
}

int	alloc_output_args(char ***output, t_split *first, int length)
{
	char	**new;
	int		count;

	count = get_arg_count(first, length);
	if (count == -1)
	{
		*output = NULL;
		return (EXIT_SUCCESS);
	}
	new = malloc(sizeof(char *) * (count + 1));
	if (new == NULL)
		return (EXIT_FAILURE);
	ft_bzero(new, sizeof(char *) * (count + 1));
	*output = new;
	return (EXIT_SUCCESS);
}

void	addback_split_list(t_split **list, t_split *new)
{
	t_split	*current;

	if (*list == NULL)
		*list = new;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

int	copy_list(t_split **copy, t_split *origin)
{
	t_split	*current;
	t_split	*new;
	int		in_par;

	current = origin->next;
	in_par = 1;
	while (current)
	{
		if (current->tok_type == PAR_CLOSE)
			in_par--;
		else if (current->tok_type == PAR_OPEN)
			in_par++;
		if (!in_par)
			break ;
		new = copy_split_elem(current);
		if (!new)
			return (destroy_split_list(copy, EXIT_FAILURE));
		addback_split_list(copy, new);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	add_file_list(t_file **files, t_split *current, t_heredocs **heredocs,
		int *length)
{
	t_file	*output;
	char	*file_name;

	output = malloc(sizeof(t_file));
	if (output == NULL)
		return (EXIT_FAILURE);
	ft_bzero(output, sizeof(t_file));
	output->fd = -1;
	file_name = ft_strdup(current->next->str);
	if (file_name == NULL)
		return (free(output), EXIT_FAILURE);
	init_file_output(output, file_name, current->tok_type, heredocs);
	addback_file_list(files, output);
	*length -= 1;
	return (EXIT_SUCCESS);
}
