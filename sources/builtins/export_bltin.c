/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:10:29 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/04 03:03:44 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**export_bltin(char **envp, char *to_add)
{
	char	**new_env;

	int (i) = 0;
	int (j) = 0;
	int (trigger) = 0;
	while (to_add[i])
	{
		if (to_add[i] == '=')
			trigger = 1;
		i++;
	}
	if (trigger == 1)
	{
		i = 0;
		while (envp[i])
			i++;
		new_env = malloc(sizeof(char *) * (i + 2));
		if (!new_env)
			return (NULL);
		i = 0;
		while (envp[j])
			new_env[i++] = envp[j++];
		new_env[i] = to_add;
		return (new_env[i + 1] = NULL, new_env);
	}
	return (envp);
}
