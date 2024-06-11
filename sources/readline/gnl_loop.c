/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:49:57 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/26 07:02:36 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	gnl_loop(t_mini *mini)
{
	int		val;

	mini->exit_status = 0;
	val = 0;
	while (1)
	{
		mini->line_count++;
		free(mini->line);
		mini->line = gnl(STDIN_FILENO);
		if (mini->line == NULL)
			break ;
		if (!only_space(mini->line))
		{
			remove_nl(mini->line);
			val = process_line(mini->line, mini);
		}
		if (val)
			return (free(mini->line), val);
	}
	return (free(mini->line), mini->exit_status);
}
