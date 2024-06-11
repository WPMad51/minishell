/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:25:09 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 20:52:59 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_args(char **args)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == 0)
		{
			tmp = args[i];
			args[i] = args[i + 1];
			j = i;
			while (args[++j])
				args[j] = args[j + 1];
			free(tmp);
		}
		i++;
	}
}

int	expand_node(t_node *node, t_mini *mini, char **wildcard_files,
		t_heredocs **heredocs)
{
	if (node->node_type != CMD)
		return (EXIT_SUCCESS);
	if (!node->first_token || dollar_expander(&node->first_token,
			mini, 0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (expand_token_list(&node->first_token, wildcard_files) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	node->cmds = parse_cmds(node->first_token, heredocs, 1, 0);
	if (node->cmds == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	expand_file(t_file *file, t_mini *mini, char **files)
{
	t_expand	*first;
	int			val;
	char		*begin;

	first = NULL;
	begin = file->file_name;
	val = expand_file_dollar(&file->file_name, mini, &first);
	if (val)
		return (val);
	if (need_trim(file->file_name))
		quote_trimmer(file->file_name);
	if (has_wildcard(file->file_name))
		val = expand_one_wildcard_redir(&file->file_name, files);
	if (val != EXIT_SUCCESS)
	{
		if (file->file_name != begin)
			free(file->file_name);
		file->file_name = begin;
		return (val);
	}
	if (file->file_name != begin)
		free(begin);
	return (EXIT_SUCCESS);
}

int	expand_file_dollar(char **file_name, t_mini *mini, t_expand **first)
{
	char	*tmp;

	if (has_dollar(*file_name))
	{
		tmp = expand(*file_name, mini, first);
		if (tmp == NULL)
			return (EXIT_FAILURE);
		if (tmp[0] == 0)
			return (free(tmp), SYNTAX_ERR_REDIR);
		else
			*file_name = tmp;
	}
	return (EXIT_SUCCESS);
}
