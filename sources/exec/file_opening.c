/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:31:12 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/05 05:11:49 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_infile(t_file *cur_file, t_mini *mini)
{
	if (mini->fd_infile > 2)
		close(mini->fd_infile);
	mini->fd_infile = open(cur_file->file_name, O_RDONLY);
	if (mini->fd_infile == -1)
	{
		mini->exit_status = 1;
		return (print_file_error(cur_file, mini), 1);
	}
	mini->infile_is_heredoc = 0;
	return (0);
}

static int	open_outfile(t_file *cur_file, t_mini *mini)
{
	if (mini->fd_outfile > 2)
		close(mini->fd_outfile);
	if (cur_file->redir_type == OUTFILE_TRUNC)
		mini->fd_outfile = open(cur_file->file_name,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (cur_file->redir_type == OUTFILE_APPEND)
		mini->fd_outfile = open(cur_file->file_name,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (mini->fd_outfile == -1)
	{
		mini->exit_status = 1;
		return (print_file_error(cur_file, mini), 1);
	}
	return (0);
}

static int	open_heredoc(t_file *cur_file, t_mini *mini)
{
	if (mini->fd_infile > 2)
		close(mini->fd_infile);
	mini->fd_infile = cur_file->fd;
	cur_file->fd = -1;
	if (mini->fd_infile == -1)
	{
		mini->exit_status = 1;
		return (1);
	}
	mini->infile_is_heredoc = 1;
	return (0);
}

static int	heredoc_and_dup(t_mini *mini, int *process_pipe)
{
	if (mini->infile_is_heredoc == 1)
	{
		heredoc_expander(&mini->fd_infile, mini, process_pipe);
		dup2(mini->fd_infile, STDIN_FILENO);
		close(mini->fd_infile);
	}
	else if (mini->infile_is_heredoc == 0 && mini->fd_infile > 2)
	{
		dup2(mini->fd_infile, STDIN_FILENO);
		close(mini->fd_infile);
	}
	if (mini->fd_outfile > 2)
	{
		dup2(mini->fd_outfile, STDOUT_FILENO);
		close(mini->fd_outfile);
	}
	return (EXIT_SUCCESS);
}

int	open_files(t_cmd *cur_cmd, t_mini *mini, char **full_files,
		int *process_pipe)
{
	t_file	*cur_file;
	int		val;

	cur_file = cur_cmd->files;
	while (cur_file)
	{
		val = expand_file(cur_file, mini, full_files);
		if (val == EXIT_FAILURE)
			return (err_printf("%s", ERR_MSG_MALLOC, NULL, NULL), EXIT_FAILURE);
		else if (val == SYNTAX_ERR_REDIR)
			return (printf_syntax_err(mini, cur_file->file_name));
		if (cur_file->redir_type == INFILE && open_infile(cur_file, mini) == 1)
			return (ERR_OP_FILE);
		else if (cur_file->redir_type == HERE_DOC && open_heredoc(cur_file,
				mini) == 1)
			return (ERR_OP_FILE);
		else if ((cur_file->redir_type == OUTFILE_APPEND
				|| cur_file->redir_type == OUTFILE_TRUNC)
			&& open_outfile(cur_file, mini) == 1)
			return (ERR_OP_FILE);
		cur_file = cur_file->next;
	}
	heredoc_and_dup(mini, process_pipe);
	return (0);
}
