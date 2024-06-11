/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bltin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:22:49 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/29 08:44:06 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_home(t_mini *mini)
{
	char	*pwd;
	char	*oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	pwd = get_env_variable(mini->env, "HOME");
	if (pwd == NULL || pwd[0] == '\0')
		return (cd_err(mini, 1), EXIT_SUCCESS);
	if (ft_strdup2(get_env_variable(mini->env, "PWD"), &oldpwd) == EXIT_FAILURE)
		return (err_printf("%s", ERR_MSG_CD_FATAL_ERR, NULL, NULL),
			free_cd(&pwd, &oldpwd), free_everything(mini, EXIT_FAILURE));
	if (ft_strdup2(get_env_variable(mini->env, "HOME"), &pwd) == EXIT_FAILURE)
		return (err_printf("%s", ERR_MSG_CD_FATAL_ERR, NULL, NULL),
			free_cd(&pwd, &oldpwd), free_everything(mini, EXIT_FAILURE));
	if (chdir(pwd) == 0)
	{
		if (change_env(mini->env, pwd, oldpwd, mini) == EXIT_FAILURE)
			return (mini->exit_status = 1, EXIT_FAILURE);
	}
	else
	{
		free_cd(&pwd, &oldpwd);
		cd_err_3(mini, pwd);
	}
	return (EXIT_SUCCESS);
}

static int	cd_oldpwd(t_mini *mini, int to_print)
{
	char	*pwd;
	char	*tmp;
	char	*oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	oldpwd = get_env_variable(mini->env, "OLDPWD");
	if (oldpwd != NULL && oldpwd[0] != '\0' && chdir(oldpwd) == 0)
	{
		pwd = get_env_variable(mini->env, "PWD");
		if (ft_strdup2(pwd, &tmp) == EXIT_FAILURE)
			return (err_printf("%s", ERR_MSG_CD_FATAL_ERR, NULL, NULL),
				free_cd(&tmp, &pwd), free_everything(mini, EXIT_FAILURE));
		if (ft_strdup2(oldpwd, &pwd) == EXIT_FAILURE)
			return (err_printf("%s", ERR_MSG_CD_FATAL_ERR, NULL, NULL),
				free_cd(&tmp, &pwd), free_everything(mini, EXIT_FAILURE));
		if (to_print == 0 && get_env_variable(mini->env, "OLDPWD"))
			printf("%s\n", get_env_variable(mini->env, "OLDPWD"));
		if (change_env(mini->env, pwd, tmp, mini) == EXIT_FAILURE)
			return (mini->exit_status = 1, EXIT_FAILURE);
		mini->exit_status = 0;
	}
	else
		cd_err_2(mini);
	return (EXIT_SUCCESS);
}

static int	cd_normal_case(t_mini *mini)
{
	char	*pwd;
	char	*oldpwd;

	pwd = NULL;
	oldpwd = NULL;
	if (ft_strdup2(get_env_variable(mini->env, "PWD"), &oldpwd) == EXIT_FAILURE)
		return (err_printf("%s", ERR_MSG_CD_FATAL_ERR, NULL, NULL),
			free_cd(&pwd, &oldpwd), free_everything(mini, EXIT_FAILURE));
	if (get_curr_dir_name(&pwd, 0) == EXIT_FAILURE)
		return (free_cd(&pwd, &oldpwd), free_everything(mini, EXIT_FAILURE));
	if (change_env(mini->env, pwd, oldpwd, mini) == EXIT_FAILURE)
	{
		mini->exit_status = 1;
		return (EXIT_FAILURE);
	}
	mini->exit_status = 0;
	return (EXIT_SUCCESS);
}

static int	cd_choose_case(t_mini *mini, char **dir)
{
	char	*res;
	char	*tmp;

	res = NULL;
	if (get_curr_dir_name(&res, 0) == EXIT_FAILURE)
		return (free(res), free_everything(mini, EXIT_FAILURE));
	if (ft_strcmp("-", dir[1]) == 0 || ft_strcmp("~-", dir[1]) == 0)
	{
		tmp = get_env_variable(mini->env, "OLDPWD");
		if (tmp == NULL || tmp[0] == '\0')
			return (mini->exit_status = 1, free(res), err_printf("%s",
					ERR_MSG_CD_OLD, NULL, NULL), EXIT_SUCCESS);
		if (cd_oldpwd(mini, ft_strcmp("-", dir[1])) == EXIT_FAILURE)
			return (free(res), EXIT_FAILURE);
	}
	else if (res && chdir(dir[1]) == 0)
	{
		if (cd_normal_case(mini) == EXIT_FAILURE)
			return (free(res), EXIT_FAILURE);
	}
	else
		cd_err_3(mini, dir[1]);
	return (free(res), EXIT_SUCCESS);
}

int	cd_bltin(char **dir, t_mini *mini, int is_child)
{
	int	res;

	if (dir[1] == NULL || (dir[1][0] == '~' && dir[1][1] == '\0'))
	{
		res = cd_home(mini);
		if (res == EXIT_FAILURE && is_child == 1)
			exit(EXIT_FAILURE);
		else if (res == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (dir[2] != NULL)
		err_printf("%s", ERR_MSG_CD_ARG, NULL, NULL);
	else
	{
		res = cd_choose_case(mini, dir);
		if (res == EXIT_FAILURE && is_child == 1)
			exit(EXIT_FAILURE);
		else if (res == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (is_child == 1)
		exit(mini->exit_status);
	return (EXIT_SUCCESS);
}
