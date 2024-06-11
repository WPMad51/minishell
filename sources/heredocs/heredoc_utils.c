/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:14:50 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/28 13:25:18 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	generate_random(char *output, int size)
{
	int		fd;
	int		rd_bytes;
	char	tmp[100];

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	while (size >= 0)
	{
		rd_bytes = read(fd, tmp, 100);
		if (rd_bytes <= 0)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
		rd_bytes = 0;
		while (rd_bytes < 100 && size >= 0)
		{
			if (tmp[rd_bytes] <= 'z' && tmp[rd_bytes] >= 'a')
				output[size--] = tmp[rd_bytes];
			rd_bytes++;
		}
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	get_hd_name(char *hd_name)
{
	char	random[35];
	int		error;

	ft_bzero(random, sizeof(char) * 35);
	ft_strlcpy(hd_name, "/tmp/here_doc_", ft_strlen("/tmp/here_doc_"));
	error = generate_random(random, 33);
	if (error)
		return (error);
	ft_strlcpy(hd_name + ft_strlen(hd_name), random, 50
		- ft_strlen("/tmp/here_doc_") - 1);
	return (EXIT_SUCCESS);
}

int	get_first_heredoc(t_heredocs **heredocs)
{
	t_heredocs	*tmp;
	t_heredocs	*current;
	int			output;

	output = (*heredocs)->fd;
	tmp = (*heredocs);
	current = tmp;
	while (current->next)
		current = current->next;
	current->next = tmp;
	*heredocs = tmp->next;
	tmp->next = NULL;
	return (output);
}

int	addback_hd_list(t_heredocs **heredocs, int fd)
{
	t_heredocs	*new;
	t_heredocs	*current;

	new = malloc(sizeof(t_heredocs));
	if (!new)
		return (EXIT_FAILURE);
	new->next = NULL;
	new->fd = fd;
	current = *heredocs;
	if (!current)
	{
		*heredocs = new;
		return (EXIT_SUCCESS);
	}
	while (current->next)
		current = current->next;
	current->next = new;
	return (EXIT_SUCCESS);
}

void	remove_hd_list(t_heredocs **first)
{
	t_heredocs	*current;
	t_heredocs	*tmp;

	current = *first;
	while (current)
	{
		tmp = current->next;
		close(current->fd);
		free(current);
		current = tmp;
	}
	*first = NULL;
}
