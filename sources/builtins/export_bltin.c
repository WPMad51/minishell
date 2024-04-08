/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:10:29 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/09 01:28:07 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**add_line(char **env, char *to_add)
{
	char	**new_env;

	int (i) = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (env);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (ft_le_xav(new_env), env);
		i++;
	}
	new_env[i] = ft_strdup(to_add);
	new_env[i + 1] = NULL;
	ft_le_xav(env);
	return (new_env);
}

static char	**replace_line(char **env, char *to_add, int i)
{
	char	**new_env;

	int (j) = 0;
	while (env[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + 1));
	if (!new_env)
		return (env);
	j = 0;
	while (env[j])
	{
		if (j == i)
			new_env[j] = ft_strdup(to_add);
		else
			new_env[j] = ft_strdup(env[j]);
		if (!new_env[j])
			return (ft_le_xav(new_env), env);
		j++;
	}
	new_env[j] = NULL;
	ft_le_xav(env);
	return (new_env);
}

static void	check_to_add(char *to_add, int *trigger)
{
	int (i) = 0;
	while (to_add[i])
	{
		if ((i == 0 && to_add[i] == '=')
			|| (to_add[i] == '=' && to_add[i - 1] == ' '))
		{
			*trigger = -1;
			printf ("bash: export: '%s': not a valid identifier\n", to_add);
			return ;
		}
		i++;
	}
}

char	**export_bltin(char **env, char *to_add)
{
	int (i) = 0;
	int (trigger) = 0;
	if (!to_add)
		return (sort_and_print_env(env), env);
	check_to_add(to_add, &trigger);
	if (trigger == -1)
		return (env);
	while (env[i])
	{
		if (ft_strncmp(env[i], to_add, ft_strlen_to_c(to_add, '=') + 1) == 0)
			return (replace_line(env, to_add, i));
		i++;
	}
	return (add_line(env, to_add));
}
