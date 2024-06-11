/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:16:28 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 23:02:10 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_process_pipe(int *process_pipe)
{
	if (process_pipe)
	{
		close(process_pipe[0]);
		close(process_pipe[1]);
	}
}

int	heredoc_expander(int *heredoc_fd, t_mini *mini, int *process_pipe)
{
	int	pipe_fd[2];
	int	pid;

	if (pipe(pipe_fd) == -1)
	{
		close_process_pipe(process_pipe);
		exit(free_everything(mini, EXIT_FAILURE));
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close_process_pipe(process_pipe);
		exit(free_everything(mini, EXIT_FAILURE));
	}
	if (pid == 0)
	{
		rl_clear_history();
		close_process_pipe(process_pipe);
		expand_in_child(*heredoc_fd, pipe_fd[1], mini);
		exit(close_all_in_child(mini, pipe_fd, *heredoc_fd, EXIT_SUCCESS));
	}
	else
		return (hd_exp_parent(heredoc_fd, pid, pipe_fd));
}

int	expand_in_child(int heredoc_fd, int write_pipe, t_mini *mini)
{
	char	*line;
	char	need_exp;
	char	*first_line;

	line = gnl(heredoc_fd);
	if (!line)
		return (EXIT_FAILURE);
	need_exp = line[0];
	first_line = line + 1;
	write_expanded_line(write_pipe, first_line, mini, need_exp);
	while (line)
	{
		free(line);
		line = gnl(heredoc_fd);
		write_expanded_line(write_pipe, line, mini, need_exp);
	}
	free(line);
	return (EXIT_SUCCESS);
}

int	hd_exp_parent(int *heredoc_fd, int pid, int *pipe_fd)
{
	int	exit_status;

	exit_status = 0;
	close(*heredoc_fd);
	*heredoc_fd = -1;
	if (close(pipe_fd[1]) == -1)
		kill(pid, SIGINT);
	waitpid(pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) != EXIT_SUCCESS)
		return (close(pipe_fd[0]), EXIT_FAILURE);
	*heredoc_fd = pipe_fd[0];
	return (EXIT_SUCCESS);
}

int	get_heredoc_content_gnl(int fd, char *limiter, t_mini *mini)
{
	char	*line;

	if (has_quote(limiter))
		write(fd, "a", 1);
	else
		write(fd, "b", 1);
	dollar_trimmer(limiter);
	quote_trimmer(limiter);
	line = NULL;
	prompt_gnl(mini->is_tty, line, fd);
	line = gnl(STDIN_FILENO);
	remove_nl(line);
	while (line && ft_strcmp(line, limiter))
	{
		prompt_gnl(mini->is_tty, line, fd);
		free(line);
		line = gnl(STDIN_FILENO);
		remove_nl(line);
	}
	return (process_final_line(line, mini, limiter));
}
