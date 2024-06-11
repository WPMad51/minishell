/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:42:16 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/30 09:39:56 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	destroy_mini(t_mini *mini, int value)
{
	if (mini->line)
	{
		free(mini->line);
		mini->line = NULL;
	}
	destroy_tab(&mini->env);
	destroy_tab(&mini->path_tab);
	destroy_tab(&mini->dir_list);
	free(mini->comand);
	return (value);
}

void	close_fds(t_mini *mini)
{
	if (mini->fd_infile > 2)
	{
		close(mini->fd_infile);
		mini->fd_infile = -1;
	}
	if (mini->fd_outfile > 2)
	{
		close(mini->fd_outfile);
		mini->fd_outfile = -1;
	}
	if (mini->save_stdin > 2)
	{
		close(mini->save_stdin);
		mini->save_stdin = -1;
	}
	if (mini->save_stdout > 2)
	{
		close(mini->save_stdout);
		mini->save_stdout = -1;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	kill_processes(t_proc **processes)
{
	t_proc	*current;

	current = *processes;
	while (current)
	{
		kill(current->pid, SIGINT);
		current = current->next;
	}
	destroy_proc_list(processes);
}

int	free_everything(t_mini *mini, int value)
{
	rl_clear_history();
	destroy_tree(&mini->ast, value);
	remove_hd_list(&mini->heredocs);
	close_fds(mini);
	kill_processes(&mini->processes);
	return (destroy_mini(mini, value));
}
