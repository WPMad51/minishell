/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:53:22 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/30 08:52:47 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_empty_args(t_cmd *first_cmd)
{
	t_cmd	*current;

	current = first_cmd;
	while (current)
	{
		check_args(current->args);
		current = current->next;
	}
}

void	trim_args(t_cmd *cmds)
{
	t_cmd	*current;
	int		i;

	current = cmds;
	while (current)
	{
		i = 0;
		while (current->args[i])
			quote_trimmer(current->args[i++]);
		current = current->next;
	}
}

int	char_gets_dolls_written_quote(char c)
{
	if (c == ' ' || c == '=' || c == 0 || c == '\"' || c == '\'' || c == ':')
		return (1);
	return (0);
}
