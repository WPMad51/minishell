/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:54:28 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/08 18:24:51 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **envp)
{
	char	**env;

	int (i) = 0;
	int (j) = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		env[i] = malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		j = 0;
		while (envp[i][j])
		{
			env[i][j] = envp[i][j];
			j++;
		}
		env[i][j] = '\0';
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	char	*dest;
	if (argc == 0 || !argv || !envp)
		return (1);
	env = get_env(envp);
	while (1)
	{
		dest = readline("minishell_try ");

		//env_bltin(env);

		//pwd_bltin();

		printf("AVANT\n");
		env_bltin(env);

		env = export_bltin(env, dest);

		printf("\n\n\n\nAPRES\n");
		env_bltin(env);

		//printf("\n\n\n");

		// env = unset_bltin(env, "PROUT");
		// env_bltin(env);

		/*A terminer*/

		// cd_bltin(argv[1]);
		// env_bltin(env);

		//echo_bltin_v1(argv[1], argv[2]);
		free(dest);
	}
	ft_le_xav(env);
	return (0);
}
