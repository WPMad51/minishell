/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_change_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:47:59 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/28 10:04:28 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_pwd(t_mini *mini, char **env_line, char **pwd, char **oldpwd)
{
	if (pwd != NULL)
	{
		free(*env_line);
		*env_line = ft_strjoin("PWD=", *pwd);
		free(*pwd);
		*pwd = NULL;
		if (*env_line == NULL)
			return (free_cd(pwd, oldpwd), cd_err(mini, 0),
				free_everything(mini, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

int	change_old(t_mini *mini, char **env_line, char **pwd, char **oldpwd)
{
	if (oldpwd != NULL)
	{
		free(*env_line);
		*env_line = ft_strjoin("OLDPWD=", *oldpwd);
		free(*oldpwd);
		*oldpwd = NULL;
		if (*env_line == NULL)
			return (free_cd(pwd, oldpwd), cd_err(mini, 0),
				free_everything(mini, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

int	change_env(char **env, char *pwd, char *oldpwd, t_mini *mini)
{
	while (*env)
	{
		if (ft_strncmp("PWD=", *env, ft_strlen("PWD=")) == 0
			|| ft_strcmp("PWD", *env) == 0)
		{
			if (change_pwd(mini, &(*env), &pwd, &oldpwd) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (ft_strncmp("OLDPWD=", *env, ft_strlen("OLDPWD=")) == 0
			|| ft_strcmp("OLDPWD", *env) == 0)
		{
			if (change_old(mini, &(*env), &pwd, &oldpwd) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		env++;
	}
	return (free_cd(&pwd, &oldpwd), mini->exit_status = 0, EXIT_SUCCESS);
}
