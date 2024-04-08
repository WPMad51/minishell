/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bltin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:22:49 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/09 00:48:06 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	change_env(char	***env, char *pwd, char *oldpwd)
{
	int (i) = 0;
	while ((*env)[i])
	{
		if (ft_strncmp("PWD=", (*env)[i], ft_strlen("PWD=")) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("PWD=", pwd);
		}
		else if (ft_strncmp("OLDPWD=", (*env)[i], ft_strlen("OLDPWD=")) == 0)
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
		i++;
	}
}

static void	cd_home(char ***env)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getenv("PWD");
	oldpwd = getenv("OLDPWD");
	if (pwd != NULL && oldpwd != NULL)
		ft_strcpy(oldpwd, pwd);
	pwd = getenv("HOME");
	if (chdir(pwd) == 0)
		change_env(env, pwd, oldpwd);
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
}

void	cd_bltin(char *dir, char ***env)
{
	char	*pwd;
	char	*oldpwd;

	if (!dir)
	{
		cd_home(env);
		return ;
	}
	if (chdir(dir) == 0)
	{
		pwd = getenv("PWD");
		oldpwd = getenv("OLDPWD");
		if (pwd != NULL && oldpwd != NULL)
			ft_strcpy(oldpwd, pwd);
		pwd = getcwd(pwd, MAX_SIZE);
		change_env(env, pwd, oldpwd);
	}
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
}
