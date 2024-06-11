/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_bltin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:45:56 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/24 21:49:43 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_export_error(t_mini *mini, int is_child)
{
	perror(ERR_MSG_EXPORT_WRITE);
	mini->exit_status = 1;
	if (is_child == 1)
		(exit(1));
	return (EXIT_SUCCESS);
}

static int	print_env_line(char *line, t_mini *mini, int is_child)
{
	char	*tmp;
	int		size_to;

	tmp = ft_strchr(line, '=');
	if (tmp != NULL)
	{
		tmp++;
		size_to = tmp - line;
		if (ft_strncmp("_=", line, 2) != 0)
		{
			if (printf("export %.*s\"%s\"\n", size_to, line, tmp) == -1)
				return (print_export_error(mini, is_child));
		}
	}
	else
	{
		if (printf("export %s\n", line) == -1)
			return (print_export_error(mini, is_child));
	}
	mini->exit_status = 0;
	return (EXIT_SUCCESS);
}

static int	print_sorted_env(char **env, t_mini *mini, int is_child)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("_=", env[i], 2) != 0)
		{
			print_env_line(env[i], mini, is_child);
			if (mini->exit_status == 1)
			{
				destroy_tab(&env);
				return (EXIT_SUCCESS);
			}
		}
		i++;
	}
	destroy_tab(&env);
	return (EXIT_SUCCESS);
}

static void	sort_env(char **env_temp, int size)
{
	char	*temp;
	int		i;

	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(env_temp[i], env_temp[i + 1]) > 0)
		{
			temp = env_temp[i + 1];
			env_temp[i + 1] = env_temp[i];
			env_temp[i] = temp;
			i = -1;
		}
		i++;
	}
}

int	sort_and_print_env(char **env, t_mini *mini, int is_child)
{
	char	**env_temp;
	int		size;

	size = 0;
	if (get_envp(env, &env_temp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!env_temp || !*env_temp)
		return (EXIT_SUCCESS);
	while (env_temp[size])
		size++;
	sort_env(env_temp, size);
	print_sorted_env(env_temp, mini, is_child);
	if (is_child == 1)
		exit(mini->exit_status);
	return (EXIT_SUCCESS);
}
