/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bltin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:28:50 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/03 17:58:58 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_new_env(char **new_env, t_mini *mini, int line_to_unset)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	while (mini->env[len])
		len++;
	while (i < len)
	{
		if (i != line_to_unset)
		{
			new_env[j] = ft_strdup(mini->env[i]);
			if (!new_env)
				return (destroy_tab(&new_env),
					unset_malloc_err(mini), mini->env);
			j++;
			i++;
		}
		else
			i++;
	}
	new_env[j] = NULL;
	return (destroy_tab(&mini->env), new_env);
}

int	replace_env(t_mini *mini, int line_to_unset)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * env_len(mini->env));
	if (!new_env)
	{
		mini->fatal_error = 1;
		return (unset_malloc_err(mini), EXIT_FAILURE);
	}
	mini->env = (get_new_env(new_env, mini, line_to_unset));
	if (mini->fatal_error == 1)
		return (unset_malloc_err(mini), EXIT_FAILURE);
	mini->exit_status = 0;
	return (EXIT_SUCCESS);
}

int	check_env(char *to_unset, char **env, int *line_to_unset)
{
	int	i;
	int	size;
	int	trigger;

	trigger = 0;
	i = 0;
	if (contains_equal(to_unset) == 1)
		return (trigger);
	while (env[i])
	{
		size = get_size(to_unset, env[i]);
		if (ft_strncmp(env[i], to_unset, size) == 0)
		{
			(*line_to_unset) = i;
			trigger = 1;
			return (trigger);
		}
		i++;
	}
	return (trigger);
}

int	unset_bltin(char **to_unset, t_mini *mini, int is_child)
{
	int		j;
	int		line_to_unset;

	j = 1;
	if (mini->env[0] == NULL)
	{
		if (is_child == 1)
			exit(EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	while (to_unset[j])
	{
		line_to_unset = 0;
		if (ft_strcmp(to_unset[j], "PATH") == 0)
				mini->is_path_uns = 1;
		if (check_env(to_unset[j], mini->env, &line_to_unset) == 1)
		{
			if (replace_env(mini, line_to_unset) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		j++;
	}
	if (is_child == 1)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
