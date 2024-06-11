/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:51:12 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 20:52:50 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_expander(t_split **line_list, t_mini *mini, int in_par)
{
	t_split		*current;
	t_expand	*first;
	char		*tmp;

	current = *line_list;
	if (!current)
		return (EXIT_FAILURE);
	first = NULL;
	while (current)
	{
		if (current->sub_tok_type == PAR)
			process_in_par(current->tok_type, &in_par);
		else if (current->sub_tok_type == REDIR)
			current = current->next;
		else if (!in_par && has_dollar(current->str))
		{
			tmp = expand(current->str, mini, &first);
			if (tmp == NULL)
				return (EXIT_FAILURE);
			free(current->str);
			current->str = tmp;
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static int	do_both_expand(t_expand **first, char *str, int *i, t_mini *mini)
{
	if (add_to_expand_list(first, str, *i) == EXIT_FAILURE
		|| add_to_expand_dollar_list(first, str, i, mini) == EXIT_FAILURE)
		return (destroy_split_list(first, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

void	get_quote_status(char c, char *is_quote)
{
	if ((c == '\'' || c == '"') && *is_quote == c)
		*is_quote = 0;
	else if ((c == '\'' || c == '"') && *is_quote == 0)
		*is_quote = c;
}

char	*expand(char *str, t_mini *mini, t_expand **first)
{
	int		i;
	char	is_quote;

	is_quote = 0;
	i = 0;
	while (str[i])
	{
		get_quote_status(str[i], &is_quote);
		if (str[i] == '$' && (!is_quote || is_quote == '"'))
		{
			if (!is_quote && do_both_expand(first, str, &i,
					mini) == EXIT_FAILURE)
				return (NULL);
			else if (is_quote && do_both_expand_quote(first, str, &i,
					mini) == EXIT_FAILURE)
				return (NULL);
			str += i;
			i = 0;
		}
		else
			i++;
	}
	if (add_to_expand_list(first, str, i) == EXIT_FAILURE)
		return (destroy_split_list(first, 0), NULL);
	return (process_list(first));
}

t_expand	*create_expand_dollar(char *str, int *i, t_mini *mini)
{
	t_expand	*output;
	int			index;

	index = 1;
	output = malloc(sizeof(t_expand));
	if (!output)
		return (NULL);
	ft_bzero(output, sizeof(t_expand));
	if (str[index + *i] == ' ' || str[index + *i] == '=' || str[index + *i] == 0
		|| str[index + *i] == ':')
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
