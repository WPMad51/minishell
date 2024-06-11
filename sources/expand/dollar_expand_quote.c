/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:46:29 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 13:43:49 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_both_expand_quote(t_expand **first, char *str, int *i, t_mini *mini)
{
	if (add_to_expand_list(first, str, *i) == EXIT_FAILURE
		|| add_to_expand_dollar_list_quote(first, str, i, mini) == EXIT_FAILURE)
		return (destroy_split_list(first, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

t_expand	*create_expand_dollar_quote(char *str, int *i, t_mini *mini)
{
	t_expand	*output;
	int			index;

	index = 1;
	output = malloc(sizeof(t_expand));
	if (!output)
		return (NULL);
	ft_bzero(output, sizeof(t_expand));
	if (char_gets_dolls_written_quote(str[index + *i]))
		get_str_output(&output->str, i, 1);
	else if (ft_isalpha(str[index + *i]) || str[index + *i] == '_')
		get_str_output_env(str, &output->str, i, mini->env);
	else if (str[index + *i] == '?')
	{
		output->str = ft_itoa(mini->exit_status);
		*i += 2;
	}
	else if (ft_isdigit(str[index + *i]) || str[index + *i] == '*')
		get_str_output(&output->str, i, 2);
	else
		get_str_output(&output->str, i, 3);
	if (output->str == NULL)
		return (free(output), NULL);
	return (output);
}

int	add_to_expand_dollar_list_quote(t_expand **first, char *str, int *i,
		t_mini *mini)
{
	t_expand	*current;

	if (!(*first))
	{
		*first = create_expand_dollar_quote(str, i, mini);
		if (!(*first))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	current = *first;
	while (current->next)
		current = current->next;
	current->next = create_expand_dollar_quote(str, i, mini);
	if (!current->next)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
