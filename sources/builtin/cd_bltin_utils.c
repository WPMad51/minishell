/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bltin_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:43:55 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/29 08:56:06 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_err(t_mini *mini, int errnum)
{
	if (errnum == 0)
	{
		mini->fatal_error = 1;
		err_printf("%s", ERR_MSG_CD_FATAL_ERR, NULL, NULL);
	}
	else if (errnum == 1)
	{
		mini->exit_status = 1;
		err_printf("%s", ERR_MSG_CD_HOME, NULL, NULL);
	}
}

void	cd_err_2(t_mini *mini)
{
	char	*old;

	mini->exit_status = 1;
	old = get_env_variable(mini->env, "OLDPWD");
	err_printf_plus("%s%s%s%s\n", (char *[4]){ERR_MSG_CD, old,
		": ", strerror(errno)}, 4);
}

void	cd_err_3(t_mini *mini, char *dir)
{
	mini->exit_status = 1;
	err_printf_plus("%s%s%s%s\n", (char *[4]){ERR_MSG_CD, dir, ": ",
		strerror(errno)}, 4);
}

void	free_cd(char **pwd, char **oldpwd)
{
	if (*pwd)
	{
		free(*pwd);
		*pwd = NULL;
	}
	if (*oldpwd)
	{
		free(*oldpwd);
		*oldpwd = NULL;
	}
}
