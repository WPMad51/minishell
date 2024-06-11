/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:58:16 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/23 11:51:59 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_expand_count(t_expand **first)
{
	int			i;
	int			char_count;
	t_expand	*current;

	char_count = 0;
	current = *first;
	while (current)
	{
		i = 0;
		while (current->str[i++])
			char_count++;
		current = current->next;
	}
	return (char_count);
}

static void	fill_expand_output(char *output, t_expand **first)
{
	int			i;
	int			index;
	t_expand	*current;

	current = *first;
	index = 0;
	current = *first;
	while (current)
	{
		i = 0;
		while (current->str[i])
			output[index++] = current->str[i++];
		current = current->next;
	}
	output[index] = 0;
}

char	*process_list(t_expand **first)
{
	int		char_count;
	char	*output;

	if (!(*first))
		return (NULL);
	char_count = get_expand_count(first);
	output = malloc(sizeof(char) * (char_count + 1));
	if (!output)
		return (destroy_split_list(first, EXIT_FAILURE), NULL);
	char_count = 0;
	fill_expand_output(output, first);
	return (destroy_split_list(first, EXIT_SUCCESS), output);
}

int	add_to_expand_dollar_list(t_expand **first, char *str, int *i, t_mini *mini)
{
	t_expand	*current;

	if (!(*first))
	{
		*first = create_expand_dollar(str, i, mini);
		if (!(*first))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	current = *first;
	while (current->next)
		current = current->next;
	current->next = create_expand_dollar(str, i, mini);
	if (!current->next)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	add_to_expand_list(t_expand **first, char *str, int i)
{
	t_expand	*current;

	current = *first;
	if (!current)
	{
		*first = create_new_expand(str, i);
		if (!(*first))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	while (current->next)
		current = current->next;
	current->next = create_new_expand(str, i);
	if (!current->next)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
