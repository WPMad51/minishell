/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:43:16 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 18:14:40 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	child(t_cmd *cur_cmd, t_mini *mini, char **file, int *pipe_fd)
{
	int	op_file;

	signal_default();
	rl_clear_history();
	destroy_proc_list(&mini->processes);
	op_file = open_files(cur_cmd, mini, file, pipe_fd);
	if (op_file == ERR_OP_FILE || op_file == EXIT_FAILURE)
	{
		remove_hd_list(&mini->heredocs);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(free_everything(mini, EXIT_FAILURE));
	}
	if (is_builtin(cur_cmd->args) == 1)
	{
		remove_hd_list(&mini->heredocs);
		if (exec_builtin_child(cur_cmd->args, mini, pipe_fd,
				cur_cmd) == EXIT_FAILURE)
			exit(free_everything(mini, EXIT_FAILURE));
	}
	else if (execute(cur_cmd, mini, pipe_fd) == EXIT_FAILURE)
		exit(free_everything(mini, EXIT_FAILURE));
	return (EXIT_FAILURE);
}

static void	parent(t_cmd *cur_cmd, int *pipe_fd, t_mini *mini)
{
	if (close(pipe_fd[1]) == -1)
		kill(mini->last_pid, SIGINT);
	else if (add_proc_list(&mini->processes, mini->last_pid) == EXIT_FAILURE)
	{
		close(pipe_fd[0]);
		exit(free_everything(mini, EXIT_FAILURE));
	}
	if (cur_cmd->next)
		dup2(pipe_fd[0], STDIN_FILENO);
	else
	{
		dup2(mini->save_stdin, STDIN_FILENO);
		dup2(mini->save_stdout, STDOUT_FILENO);
	}
	close(pipe_fd[0]);
}

static int	init_exec_loop(t_mini *mini, int *pipe_fd)
{
	reset_fds(mini);
	if (set_path_tab(mini) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pipe(pipe_fd) == -1)
		exit(free_everything(mini, EXIT_FAILURE));
	mini->last_pid = fork();
	if (mini->last_pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(free_everything(mini, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

void	remove_from_hd_list(int fd, t_heredocs **heredocs, int to_close)
{
	t_heredocs	*current;
	t_heredocs	*tmp;

	current = *heredocs;
	if (to_close)
		close(fd);
	if (!current)
		return ;
	if ((*heredocs)->fd == fd)
	{
		tmp = (*heredocs)->next;
		free(current);
		*heredocs = tmp;
		return ;
	}
	while (current && current->next)
	{
		if (current->next->fd == fd)
		{
			tmp = current->next->next;
			free(current->next);
			current->next = tmp;
		}
		current = current->next;
	}
}

int	exec_loop(t_node *cur, t_mini *mini, char **full_file)
{
	int		pipe_fd[2];
	t_cmd	*cur_cmd;

	cur_cmd = cur->cmds;
	while (cur_cmd)
	{
		if (init_exec_loop(mini, pipe_fd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		signal(SIGINT, SIG_IGN);
		if (mini->last_pid == 0)
			child(cur_cmd, mini, full_file, pipe_fd);
		else
		{
			close_hd(cur_cmd, &mini->heredocs);
			parent(cur_cmd, pipe_fd, mini);
		}
		mini->pid_num++;
		cur_cmd = cur_cmd->next;
		destroy_tab(&mini->path_tab);
	}
	return (EXIT_SUCCESS);
}
