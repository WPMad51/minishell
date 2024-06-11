/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:23:09 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/28 07:12:47 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	dup_line(char *envp_line, char **env_line)
{
	int	i;

	(*env_line) = malloc(sizeof(char) * (ft_strlen(envp_line) + 1));
	if ((*env_line) == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (envp_line[i])
	{
		(*env_line)[i] = envp_line[i];
		i++;
	}
	(*env_line)[i] = '\0';
	return (EXIT_SUCCESS);
}

int	get_envp(char **envp, char ***mini_env)
{
	char	**env;
	int		i;

	i = 0;
	*mini_env = NULL;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (EXIT_FAILURE);
	ft_bzero(env, sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		if (dup_line(envp[i], &env[i]) == EXIT_FAILURE)
			return (destroy_tab(&env), EXIT_FAILURE);
		i++;
	}
	env[i] = NULL;
	*mini_env = env;
	return (EXIT_SUCCESS);
}

int	set_hiden_env(t_mini *mini)
{
	char	*buf;

	buf = NULL;
	mini->env = malloc(sizeof(char *) * 5);
	if (!mini->env)
		return (EXIT_FAILURE);
	mini->env[0] = ft_strdup("OLDPWD");
	if (!mini->env[0])
		return (destroy_tab(&mini->env), EXIT_FAILURE);
	buf = getcwd(buf, MAX_SIZE);
	mini->env[1] = ft_strjoin("PWD=", buf);
	if (!mini->env[1])
		return (destroy_tab(&mini->env), EXIT_FAILURE);
	mini->env[2] = ft_strdup("SHLVL=1");
	if (!mini->env[2])
		return (destroy_tab(&mini->env), EXIT_FAILURE);
	mini->env[3] = ft_strdup("_=/usr/bin/env");
	if (!mini->env[3])
		return (destroy_tab(&mini->env), EXIT_FAILURE);
	mini->env[4] = NULL;
	mini->is_env_i = 1;
	return (EXIT_SUCCESS);
}
