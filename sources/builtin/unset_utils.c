/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:27:05 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/29 08:55:38 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	unset_malloc_err(t_mini *mini)
{
	mini->fatal_error = 1;
	err_printf("%s", ERR_MSG_UNSET_FAT_ERR, NULL, NULL);
}
