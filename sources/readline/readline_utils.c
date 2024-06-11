/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:22 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/26 07:01:36 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_space(char *line)
{
	while (*line && *line != '\n')
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

void	remove_nl(char *line)
{
	if (!line)
		return ;
	while (*line)
	{
		if (*line == '\n')
		{
			*line = 0;
			return ;
		}
		line++;
	}
}
