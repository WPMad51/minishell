/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:58:05 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/08 20:45:51 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_bltin(char **envp)
{
	int (i) = 0;
	if (envp && *envp)
	{
		while (envp[i])
		{
			if (ft_strnstr(envp[i], "=", ft_strlen(envp[i])))
				printf("%s\n", envp[i]);
			i++;
		}
	}
}
