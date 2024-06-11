/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:26:58 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/29 08:45:48 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_fds(t_mini *mini)
{
	mini->fd_infile = 0;
	mini->fd_outfile = 1;
}

int	set_path_tab(t_mini *mini)
{
	mini->env_path = get_env_variable_2(mini->env, "PATH=", mini);
	if (!mini->env_path && mini->is_env_i == 1 && mini->is_path_uns == 0)
	{
		mini->env_path = ft_strdup(ENV_I_PATH);
		if (!mini->env_path)
			return (err_printf("%s", ERR_MSG_MALLOC, NULL, NULL), EXIT_FAILURE);
		mini->is_path_empty = 0;
	}
	if (!mini->env_path && mini->is_path_empty == 0)
		return (err_printf("%s", "Error\n", NULL, NULL), EXIT_FAILURE);
	if (mini->is_path_empty == 0)
	{
		mini->path_tab = ft_split(mini->env_path, ':');
		if (!mini->path_tab)
			return (err_printf("%s", ERR_MSG_MALLOC, NULL, NULL), EXIT_FAILURE);
	}
	else
		mini->path_tab = NULL;
	return (EXIT_SUCCESS);
}

void	close_hd(t_cmd *cmd, t_heredocs **heredocs)
{
	t_file	*cur;

	cur = cmd->files;
	if (!cur)
		return ;
	while (cur->next)
		cur = cur->next;
	if (cur->redir_type == HERE_DOC)
	{
		remove_from_hd_list(cur->fd, heredocs, 1);
		cur->fd = -1;
	}
}
