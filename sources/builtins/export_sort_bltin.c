/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_bltin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:45:56 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/08 19:16:19 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_sorted_env(char **env)
{
	int (i) = 0;
	while (env[i])
	{
		if (ft_strncmp("_=", env[i], 2) != 0)
			printf("%s%s\n", "declare -x ", env[i]);
		i++;
	}
}

void	sort_and_print_env(char **env)
{
	char	**env_temp;
	char	*temp;

	int (i) = 0;
	int (size) = 0;
	env_temp = get_envp(env);
	while (env_temp[size])
		size++;
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
	print_sorted_env(env_temp);
	ft_le_xav(env_temp);
}
