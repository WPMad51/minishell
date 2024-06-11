/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:32:56 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/22 16:01:54 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_on_failure(t_mini *mini)
{
	destroy_tree(&mini->ast, EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	free_at_the_end(t_mini *mini)
{
	destroy_tree(&mini->ast, EXIT_SUCCESS);
	if (mini->env)
		ft_le_xav(mini->env);
	if (mini->path_tab)
		ft_le_xav(mini->path_tab);
	return (EXIT_SUCCESS);
}
