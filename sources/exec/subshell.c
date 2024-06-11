/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:41:51 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/05 05:16:42 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	roll_back_one(t_heredocs **heredocs)
{
	t_heredocs	*current;
	t_heredocs	*tmp;

	current = *heredocs;
	tmp = current;
	while (current->next)
	{
		tmp = current;
		current = current->next;
	}
	if (current == *heredocs)
		return ;
	tmp->next = NULL;
	current->next = *heredocs;
	*heredocs = current;
}

static void	roll_back_heredocs(int rolls, t_heredocs **heredocs)
{
	while (rolls--)
		roll_back_one(heredocs);
}

int	subshell_magik(t_cmd *cur_cmd, t_mini *mini)
{
	t_split	*copy;

	copy = cur_cmd->copy;
	cur_cmd->copy = NULL;
	mini->is_subshell = 1;
	mini->infile_is_heredoc = 0;
	mini->fd_infile = 0;
	mini->fd_outfile = 1;
	close(mini->save_stdin);
	close(mini->save_stdout);
	mini->save_stdin = dup(STDIN_FILENO);
	mini->save_stdout = dup(STDOUT_FILENO);
	roll_back_heredocs(cur_cmd->hd_rolls, &mini->heredocs);
	destroy_tree(&mini->ast, EXIT_SUCCESS);
	destroy_tab(&mini->path_tab);
	destroy_tab(&mini->dir_list);
	if (create_tree(&mini->ast, &copy) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (select_node(mini->ast, mini) == EXIT_FAILURE)
		return (remove_hd_list(&mini->heredocs), destroy_tree(&mini->ast,
				EXIT_FAILURE));
	return (free_everything(mini, mini->exit_status));
}
