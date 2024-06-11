/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:13:18 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 13:43:23 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char **arg)
{
	if (!arg)
		return (0);
	if (arg[0])
	{
		if (ft_strcmp(arg[0], "cd") == 0)
			return (1);
		if (ft_strcmp(arg[0], "echo") == 0)
			return (1);
		if (ft_strcmp(arg[0], "env") == 0)
			return (1);
		if (ft_strcmp(arg[0], "exit") == 0)
			return (1);
		if (ft_strcmp(arg[0], "export") == 0)
			return (1);
		if (ft_strcmp(arg[0], "pwd") == 0)
			return (1);
		if (ft_strcmp(arg[0], "unset") == 0)
			return (1);
	}
	return (0);
}

int	exec_builtin_child(char **arg, t_mini *mini, int *pipe_fd, t_cmd *cur_cmd)
{
	close(pipe_fd[0]);
	close(mini->save_stdin);
	close(mini->save_stdout);
	if (cur_cmd->next != NULL && mini->fd_outfile < 3)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	if (ft_strcmp(arg[0], "cd") == 0)
		return (cd_bltin(cur_cmd->args, mini, 1));
	else if (ft_strcmp(arg[0], "echo") == 0)
		return (echo_bltin(arg, mini, 1));
	else if (ft_strcmp(arg[0], "env") == 0)
		return (env_bltin(mini->env, mini, 1));
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (exit_bltin(mini, cur_cmd->args, 1));
	else if (ft_strcmp(arg[0], "export") == 0)
		return (export_bltin(cur_cmd->args, mini, 1));
	else if (ft_strcmp(arg[0], "pwd") == 0)
		return (pwd_bltin(mini, cur_cmd->args, 1));
	else if (ft_strcmp(arg[0], "unset") == 0)
		return (unset_bltin(arg, mini, 1));
	exit(free_everything(mini, mini->exit_status));
}

static int	process_op_file(int op_file)
{
	if (op_file == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (op_file == SYNTAX_ERR_REDIR)
		return (SYNTAX_ERR_REDIR);
	else
		return (EXIT_SUCCESS);
}

int	exec_builtin_parent(t_cmd *cur_cmd, t_mini *mini, char ***full_file)
{
	int	op_file;

	reset_fds(mini);
	op_file = open_files(cur_cmd, mini, *full_file, NULL);
	if (op_file)
		return (destroy_tab(full_file), process_op_file(op_file));
	destroy_tab(full_file);
	if (ft_strcmp(cur_cmd->args[0], "cd") == 0)
		return (cd_bltin(cur_cmd->args, mini, 0));
	else if (ft_strcmp(cur_cmd->args[0], "echo") == 0)
		return (echo_bltin(cur_cmd->args, mini, 0));
	else if (ft_strcmp(cur_cmd->args[0], "env") == 0)
		return (env_bltin(mini->env, mini, 0));
	else if (ft_strcmp(cur_cmd->args[0], "exit") == 0)
		return (exit_bltin(mini, cur_cmd->args, 0));
	else if (ft_strcmp(cur_cmd->args[0], "export") == 0)
		return (export_bltin(cur_cmd->args, mini, 0));
	else if (ft_strcmp(cur_cmd->args[0], "pwd") == 0)
		return (pwd_bltin(mini, cur_cmd->args, 0));
	else if (ft_strcmp(cur_cmd->args[0], "unset") == 0)
		return (unset_bltin(cur_cmd->args, mini, 0));
	return (EXIT_SUCCESS);
}
