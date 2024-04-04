/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:28:50 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/04 03:04:49 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_new_env(char **env, char **new_env, char *to_unset)
{
	int (i) = 0;
	int (j) = 0;
	int (len) = 0;
	while (env[len])
		len++;
	while (i < len)
	{
		if (ft_strncmp(env[i], to_unset, ft_strlen(to_unset)) == 0)
			i++;
		new_env[j] = env[i];
		j++;
		i++;
	}
	new_env[j] = NULL;
	// if (env)
	// 	free(env);
	return (new_env);
}

char	**unset_bltin(char **envp, char *to_unset)
{
	char	**new_env;

	int	(i) = 0;
	int	(size) = 0;
	int	(trigger) = 0;
	while (envp[i])
	{
		size = ft_strlen_to_c(envp[i], '=');
		if (size == (int)ft_strlen(to_unset))
		{
			if (ft_strncmp(envp[i], to_unset, size) == 0)
				trigger = 1;
		}
		i++;
	}
	if (trigger == 1)
	{
		new_env = malloc(sizeof(char *) * (i + 1));
		if (!new_env)
			return (NULL);
		return (get_new_env(envp, new_env, to_unset));
	}
	return (envp);
}
