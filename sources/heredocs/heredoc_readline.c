/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:28:39 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 18:11:14 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_result(int pid, t_mini *mini)
{
	int	exit_status;

	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &exit_status, 0);
	signal_ms();
	if (WIFEXITED(exit_status))
	{
		if (WEXITSTATUS(exit_status) == E_STATUS_SIGINT)
			mini->last_exit_signaled = 1;
		return (WEXITSTATUS(exit_status));
	}
	else
		return (EXIT_FAILURE);
}

int	get_heredoc_content_rl(int write_fd, int read_fd, char *limiter,
		t_mini *mini)
{
	int	pid;
	int	value;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (!pid)
	{
		rl_clear_history();
		close(read_fd);
		value = get_heredoc_content_rl_child(write_fd, limiter, mini);
		close(write_fd);
		destroy_split_list(&mini->split_list, value);
		exit(free_everything(mini, value));
	}
	else
		return (process_result(pid, mini));
}

int	get_heredoc_content_rl_child(int fd, char *limiter, t_mini *mini)
{
	char	*line;

	if (has_quote(limiter))
		write(fd, "a", 1);
	else
		write(fd, "b", 1);
	dollar_trimmer(limiter);
	quote_trimmer(limiter);
	line = readline(">");
	while (line && ft_strcmp(line, limiter))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	return (process_final_line(line, mini, limiter));
}
