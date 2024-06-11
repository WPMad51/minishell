/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:31:31 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/20 13:38:01 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_split	*create_list_elem(char *str)
{
	t_split	*out;

	out = malloc(sizeof(t_split));
	if (!out)
		return (NULL);
	ft_bzero(out, sizeof(t_split));
	out->str = ft_strdup(str);
	out->tok_type = CMD;
	if (!out->str)
	{
		free(out);
		return (NULL);
	}
	return (out);
}

int	has_wildcard(char *str)
{
	char	is_quote;

	is_quote = 0;
	if (str == NULL || *str == '$')
		return (0);
	while (*str)
	{
		if (is_quote == *str)
			is_quote = 0;
		else if (is_quote == 0 && (*str == '\'' || *str == '\"'))
			is_quote = *str;
		else if (*str == '*' && !is_quote)
			return (1);
		str++;
	}
	return (0);
}

void	w_free_trim(char **trim)
{
	int	i;

	i = 0;
	while (i < 3)
		free(trim[i++]);
}

int	add_back_wildcard_list(t_split **first, char *str)
{
	t_split	*new;
	t_split	*current;

	new = create_list_elem(str);
	if (!new)
		return (EXIT_FAILURE);
	current = *first;
	if (!current)
	{
		*first = new;
		return (EXIT_SUCCESS);
	}
	while (current->next)
		current = current->next;
	current->next = new;
	return (EXIT_SUCCESS);
}

char	*get_wildcard_result(char *front_offset, char *file, char *back_offset)
{
	char	*tmp;
	char	*tmp2;

	if (front_offset)
		tmp = ft_strjoin(front_offset, file);
	else
		tmp = ft_strdup(file);
	if (!tmp)
		return (NULL);
	if (back_offset)
		tmp2 = ft_strjoin(tmp, back_offset);
	else
		tmp2 = ft_strdup(tmp);
	free(tmp);
	return (tmp2);
}
