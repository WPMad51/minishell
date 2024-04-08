/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:28:50 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/09 01:49:50 by cdutel           ###   ########.fr       */
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
		if (ft_strncmp(env[i], to_unset, ft_strlen(to_unset)) != 0)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env)
				return (ft_le_xav(new_env), env);
			j++;
			i++;
		}
		else
			i++;
	}
	new_env[j] = NULL;
	ft_le_xav(env);
	return (new_env);
}

char	**unset_bltin(char **env, char *to_unset)
{
	char	**new_env;

	int (i) = 0;
	int (size) = 0;
	int (trigger) = 0;
	while (env[i])
	{
		size = ft_strlen_to_c(env[i], '=');
		if (size == (int)ft_strlen(to_unset))
		{
			if (ft_strncmp(env[i], to_unset, size) == 0)
				trigger = 1;
		}
		i++;
	}
	if (trigger == 1)
	{
		new_env = malloc(sizeof(char *) * i);
		if (!new_env)
			return (env);
		return (get_new_env(env, new_env, to_unset));
	}
	return (env);
}
