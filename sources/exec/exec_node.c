/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:44:21 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 13:43:37 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_exit_status(t_mini *mini, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT && printf("\n"))
	{
		mini->exit_status = 130;
		mini->last_exit_signaled = 1;
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		err_printf("%s", "Quit (core dumped)\n", NULL, NULL);
		mini->exit_status = 131;
	}
	else if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
}

static void	waiting_loop(t_mini *mini)
{
	int	pid;
	int	status;

	status = 0;
	while (mini->pid_num)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == mini->last_pid)
			get_exit_status(mini, status);
		remove_proc_from_list(&mini->processes, pid);
		mini->pid_num--;
	}
	signal_ms();
}

int	exec_node(t_node *cur, t_mini *mini)
{
	int	loop_result;

	if (get_files(&mini->dir_list) != EXIT_SUCCESS)
		return (err_printf("%s", ERR_MSG_GET_FILES, NULL, NULL), EXIT_FAILURE);
	if (expand_node(cur, mini, mini->dir_list, &mini->heredocs) != EXIT_SUCCESS)
		return (destroy_tab(&mini->dir_list), err_printf("%s",
				ERR_MSG_EXPAND_NODES, NULL, NULL));
	if (is_builtin(cur->cmds->args) == 1 && cur->cmds->next == NULL)
		return (exec_builtin_parent(cur->cmds, mini, &mini->dir_list));
	mini->pid_num = 0;
	loop_result = exec_loop(cur, mini, mini->dir_list);
	waiting_loop(mini);
	if (loop_result == EXIT_FAILURE)
		return (destroy_tab(&mini->dir_list), EXIT_FAILURE);
	return (destroy_tab(&mini->dir_list), EXIT_SUCCESS);
}
