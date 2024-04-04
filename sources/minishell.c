/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:54:28 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/04 11:32:30 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 0 || !argv || !envp)
		return (1);
	//env_bltin(envp);

	//pwd_bltin();

	// envp = export_bltin(envp, argv[1]);
	// env_bltin(envp);

	//printf("\n\n\n");

	// envp = unset_bltin(envp, "PROUT");
	// env_bltin(envp);

	/*A terminer*/

	// cd_bltin(argv[1]);
	// env_bltin(envp);

	echo_bltin_v1(argv[1], argv[2]);
	return (0);
}
