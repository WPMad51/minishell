/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:48:19 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/25 16:33:03 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_proc_list(t_proc **processes, int pid)
{
	t_proc	*new;

	new = malloc(sizeof(t_proc));
	if (!new)
		return (EXIT_FAILURE);
	new->pid = pid;
	new->next = NULL;
	if (*processes == NULL)
		*processes = new;
	else
	{
		new->next = *processes;
		*processes = new;
	}
	return (EXIT_SUCCESS);
}

void	remove_proc_from_list(t_proc **processes, int pid)
{
	t_proc	*current;
	t_proc	*tmp;

	if (*processes == NULL)
		return ;
	if ((*processes)->pid == pid)
	{
		tmp = *processes;
		*processes = (*processes)->next;
		free(tmp);
		return ;
	}
	current = (*processes);
	while (current->next)
	{
		if (current->next->pid == pid)
		{
			tmp = current->next;
			current->next = tmp->next;
			free(tmp);
			return ;
		}
		current = current->next;
	}
}

void	destroy_proc_list(t_proc **processes)
{
	t_proc	*current;
	t_proc	*tmp;

	current = *processes;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*processes = NULL;
}
