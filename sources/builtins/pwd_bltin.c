/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:16:40 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/09 01:24:53 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_bltin(void)
{
	char	*wd;

	wd = NULL;
	wd = getcwd(wd, MAX_SIZE);
	if (!wd)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		return ;
	}
	if (write(1, wd, ft_strlen(wd)) == -1)
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	if (write(1, "\n", 1) == -1)
		write(2, strerror(errno), ft_strlen(strerror(errno)));
}
