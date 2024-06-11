/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:06:16 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/28 12:47:50 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dir(char *path)
{
	DIR	*dir_fd;
	int	error;

	dir_fd = opendir(path);
	error = errno;
	if (!dir_fd)
	{
		if (error == EACCES)
			return (1);
		return (0);
	}
	closedir(dir_fd);
	return (1);
}

void	destroy_tab(char ***output)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*output == NULL)
		return ;
	while ((*output)[i])
	{
		tmp = (*output)[i];
		(*output)[i] = NULL;
		free(tmp);
		i++;
	}
	free(*output);
	*output = NULL;
}

int	ft_is_quote(char c)
{
	return (c == '\'' || c == '"');
}
