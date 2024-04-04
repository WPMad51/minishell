/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bltin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 01:22:49 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/04 09:29:59 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_bltin(char *dir)
{
	char	*pwd = NULL;
	char	*oldpwd = NULL;
	char	*pwd_ptr = NULL;

	if (!dir)
		return ;
	if (chdir(dir) == 0)
	{
		pwd = getenv("PWD");
		printf("pwd = %s\n", pwd);
		//write(1, "ok1", 4);
		oldpwd = getenv("OLDPWD");
		printf("\noldpwd = %s\n", oldpwd);
		//write(1, "ok2", 4);
		if (pwd != NULL && oldpwd != NULL)
			oldpwd = ft_strcpy(oldpwd, pwd);
		//write(1, "ok3", 4);
		if (pwd != NULL)
		{
			pwd = &pwd[-ft_strlen("PWD=")];
			//write(1, "ok4", 4);
			pwd_ptr = getcwd(pwd_ptr, 100);
			//write(1, "ok5", 4);
			printf("\npwd = %s\npwd_ptr = %s\n", pwd, pwd_ptr);
			pwd = ft_strcpy(pwd, pwd_ptr);
			//write(1, "ok6", 4);
			free(pwd_ptr);
			//write(1, "ok7\n", 5);
		}
	}

}
