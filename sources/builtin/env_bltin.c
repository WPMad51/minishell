/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@42student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:58:05 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/22 15:06:02 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_env_error(t_mini *mini, int is_child)
{
	perror(ERR_MSG_ENV_WRITE);
	mini->exit_status = 125;
	if (is_child == 1)
		exit(125);
	return (EXIT_SUCCESS);
}

int	env_bltin(char **envp, t_mini *mini, int is_child)
{
	int	i;

	i = 0;
	if (envp && *envp)
	{
		while (envp[i])
		{
			if (ft_strnstr(envp[i], "=", ft_strlen(envp[i])))
			{
				if (printf("%s\n", envp[i]) == -1)
					return (print_env_error(mini, is_child));
			}
			i++;
		}
	}
	mini->exit_status = 0;
	if (is_child == 1)
		exit(0);
	return (EXIT_SUCCESS);
}
