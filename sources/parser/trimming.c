/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimming.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:37:35 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/23 14:52:42 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trimming_process(t_split **first)
{
	t_split	*current;

	if (*first == NULL)
		return (EXIT_SUCCESS);
	current = *first;
	while (current)
	{
		if (current->sub_tok_type == REDIR)
			current = current->next;
		else if (need_trim(current->str) == 1 && !has_wildcard(current->str))
			quote_trimmer(current->str);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	need_trim(char *str)
{
	char	is_quote;

	is_quote = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && is_quote == 0)
			is_quote = *str;
		else if ((*str == '\'' || *str == '"') && is_quote == *str)
			return (1);
		str++;
	}
	if (is_quote)
		return (0);
	return (0);
}
