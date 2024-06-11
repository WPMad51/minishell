/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:07:22 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/23 15:10:36 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	destroy_split_list(t_split **first, int return_val)
{
	t_split	*current;
	t_split	*tmp;

	current = *first;
	if (!current)
		return (return_val);
	while (current)
	{
		tmp = current->next;
		free(current->str);
		free(current);
		current = tmp;
	}
	*first = NULL;
	return (return_val);
}

void	destroy_split(t_split *split)
{
	if (!split)
		return ;
	if (split->str)
		free(split->str);
	free(split);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c <= 13 && c > 8))
		return (1);
	return (0);
}

void	destroy_dir_list(t_dir **first)
{
	t_dir	*current;
	t_dir	*tmp;

	if (!(*first))
		return ;
	current = *first;
	while (current)
	{
		tmp = current->next;
		free(current->name);
		free(current);
		current = tmp;
	}
	*first = NULL;
}

int	addback_dir_list(t_dir **first, char *str)
{
	t_dir	*new;
	t_dir	*current;

	new = malloc(sizeof(t_dir));
	if (!new)
		return (EXIT_FAILURE);
	new->name = ft_strdup(str);
	if (!new->name)
		return (free(new), EXIT_FAILURE);
	new->next = NULL;
	if (!(*first))
	{
		*first = new;
		return (EXIT_SUCCESS);
	}
	current = *first;
	while (current->next)
		current = current->next;
	current->next = new;
	return (EXIT_SUCCESS);
}
