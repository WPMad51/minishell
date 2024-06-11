/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:58:36 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 20:18:53 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t	g_global;

static int	test_fds(int fd, int fd2)
{
	if (fd < 0)
	{
		if (fd2 > 0)
			close(fd2);
		return (EXIT_FAILURE);
	}
	if (fd2 < 0)
	{
		if (fd > 0)
			close(fd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	get_hd_file(char *limiter, t_mini *mini)
{
	char	heredoc[50];
	int		fd;
	int		fd2;
	int		value;

	ft_bzero(heredoc, sizeof(char) * 50);
	value = get_hd_name(heredoc);
	if (value)
		return (value);
	fd = open(heredoc, O_CREAT | O_WRONLY, 0644);
	fd2 = open(heredoc, O_RDONLY);
	unlink(heredoc);
	if (test_fds(fd, fd2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (mini->is_tty)
		value = get_heredoc_content_rl(fd, fd2, limiter, mini);
	else
		value = get_heredoc_content_gnl(fd, limiter, mini);
	close(fd);
	if (value)
		return (close(fd2), value);
	if (addback_hd_list(&mini->heredocs, fd2) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
