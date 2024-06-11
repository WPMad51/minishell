/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_first_read.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:53:00 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/09 20:19:01 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fill_new_split_elem(char *line, int *i, char *str, int count);

int	line_parser(char *line, t_split **line_list)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] && add_arg_to_list(line, &i, line_list) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	add_arg_to_list(char *line, int *i, t_split **first_elem)
{
	t_split	*current;

	current = *first_elem;
	if (!current)
	{
		*first_elem = create_new_split_elem(line, i);
		if (!*first_elem)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	while (current->next)
		current = current->next;
	current->next = create_new_split_elem(line, i);
	if (!current->next)
		return (destroy_split_list(first_elem, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

t_split	*create_new_split_elem(char *line, int *i)
{
	int		count;
	t_split	*output;

	output = malloc(sizeof(t_split));
	if (!output)
		return (NULL);
	count = get_char_count(line, i);
	output->str = malloc(sizeof(char) * (count + 1));
	if (!output->str)
	{
		free(output);
		return (NULL);
	}
	fill_new_split_elem(line, i, output->str, count);
	*i += count;
	output->next = NULL;
	return (output);
}

static void	fill_new_split_elem(char *line, int *i, char *str, int count)
{
	str[count] = 0;
	while (count)
	{
		str[count - 1] = line[*i + count - 1];
		count--;
	}
}

int	get_char_count(char *line, int *i)
{
	char	is_quote;
	int		count;

	is_quote = 0;
	count = is_token(&line[*i]);
	if (count)
		return (count);
	while (line[*i + count] && !((ft_isspace(line[*i + count])
				|| is_token(&line[*i + count])) && is_quote == 0))
	{
		if ((line[*i + count] == '\'' || line[*i + count] == '"')
			&& is_quote == line[*i + count])
			is_quote = 0;
		else if ((line[*i + count] == '\'' || line[*i + count] == '"')
			&& is_quote == 0)
			is_quote = line[*i + count];
		count++;
	}
	return (count);
}
