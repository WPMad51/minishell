/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:22:18 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 20:19:40 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	addback_file_list(t_file **files, t_file *new_file)
{
	t_file	*current;

	current = *files;
	if (!current)
		*files = new_file;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_file;
	}
}

int	get_arg_count(t_split *start, int length)
{
	int		redir_count;
	int		i;
	t_split	*current;

	i = 0;
	redir_count = 0;
	current = start;
	if (!current)
		return (0);
	if (current->tok_type == PAR_OPEN)
		return (-1);
	while (current && i < length)
	{
		if (current->tok_type == REDIR)
			redir_count++;
		i++;
		current = current->next;
	}
	return (length - 2 * redir_count);
}

void	init_file_output(t_file *output, char *str, t_tok_type redir_type,
		t_heredocs **heredocs)
{
	if (redir_type == INF || redir_type == HD)
	{
		output->redir_type = INFILE;
		if (redir_type == INF)
			output->file_name = str;
		else
		{
			free(str);
			output->fd = get_first_heredoc(heredocs);
			output->redir_type++;
		}
	}
	else if (redir_type == OUTF_APPEND || redir_type == OUTF_TRUNC)
	{
		output->file_name = str;
		output->redir_type = OUTFILE_TRUNC;
		if (redir_type == OUTF_APPEND)
			output->redir_type++;
	}
}

int	destroy_cmds_list(t_cmd **first_cmds, int value)
{
	t_cmd	*current;
	t_cmd	*tmp;
	int		i;

	current = *first_cmds;
	while (current)
	{
		tmp = current->next;
		destroy_file_list(&current->files);
		i = 0;
		if (current->args)
		{
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		else
			destroy_split_list(&current->copy, value);
		current->args = NULL;
		free(current);
		current = tmp;
	}
	*first_cmds = NULL;
	return (value);
}

void	destroy_file_list(t_file **first)
{
	t_file	*current;
	t_file	*tmp;

	current = *first;
	while (current)
	{
		tmp = current->next;
		if (current->file_name)
			free(current->file_name);
		if (current->fd >= 0)
		{
			close(current->fd);
			current->fd = -1;
		}
		free(current);
		current = tmp;
	}
	*first = NULL;
}
