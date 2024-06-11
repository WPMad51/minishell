/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:10:29 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 07:40:50 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**add_line(char **env, char *to_add, t_mini *mini)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (export_error(mini, 0, 0), env);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (destroy_tab(&new_env), export_error(mini, 0, 0), env);
		i++;
	}
	new_env[i] = ft_strdup(to_add);
	if (!new_env[i])
		return (destroy_tab(&new_env), export_error(mini, 0, 0), env);
	new_env[i + 1] = NULL;
	destroy_tab(&env);
	if (ft_strncmp(to_add, "PATH=", ft_strlen("PATH=")) == 0)
		mini->is_path_empty = 0;
	return (new_env);
}

static char	**replace_line(char **env, char *to_add, int i, t_mini *mini)
{
	char	**new_env;
	int		j;

	j = 0;
	while (env[j])
		j++;
	new_env = malloc(sizeof(char *) * (j + 1));
	if (!new_env)
		return (export_error(mini, 0, 0), env);
	j = 0;
	while (env[j])
	{
		if (j == i)
			new_env[j] = ft_strdup(to_add);
		else
			new_env[j] = ft_strdup(env[j]);
		if (!new_env[j])
			return (destroy_tab(&new_env), export_error(mini, 0, 0), env);
		j++;
	}
	new_env[j] = NULL;
	destroy_tab(&env);
	return (new_env);
}

static void	test_env(char *to_add, int trigger, t_mini *mini)
{
	int	i;
	int	size;

	i = 0;
	while (mini->env[i])
	{
		size = get_size(to_add, mini->env[i]);
		if (ft_strncmp(mini->env[i], to_add, size) == 0)
		{
			if (contains_equal(to_add) == 0)
			{
				trigger = 1;
				break ;
			}
			mini->env = replace_line(mini->env, to_add, i, mini);
			if (mini->fatal_error == 1)
				return ;
			trigger = 1;
		}
		i++;
	}
	if (trigger == 0)
		mini->env = add_line(mini->env, to_add, mini);
}

static void	check_and_test(t_mini *mini, char *to_add, int *error, int *trigger)
{
	*trigger = 0;
	if (*error == 1 || *error == 2)
		check_to_add(mini, to_add, trigger);
	else
		*error = check_to_add(mini, to_add, trigger);
	if (*trigger != -1)
		test_env(to_add, (*trigger), mini);
}

int	export_bltin(char **to_add, t_mini *mini, int is_child)
{
	int	j;
	int	trigger;
	int	error;

	error = 0;
	if (to_add[1] == NULL)
		return (sort_and_print_env(mini->env, mini, is_child));
	j = 1;
	while (to_add[j])
	{
		check_and_test(mini, to_add[j], &error, &trigger);
		if (mini->fatal_error == 1)
		{
			if (is_child == 1)
				exit(1);
			return (EXIT_FAILURE);
		}
		j++;
	}
	mini->exit_status = error;
	if (is_child == 1)
		exit(mini->exit_status);
	return (EXIT_SUCCESS);
}
