/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:46:29 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/05 08:01:03 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_exec_error(t_mini *mini, char *cur_cmd, char *err_msg)
{
	err_printf("%s%s%s", ERR_MSG_JM, cur_cmd, err_msg);
	exit(free_everything(mini, 127));
}

static int	set_simple_command(t_cmd *cur_cmd, t_mini *mini)
{
	int	i;

	if ((mini->path_tab == NULL && mini->is_path_empty == 1))
		print_exec_error(mini, cur_cmd->args[0], ERR_MSG_FIDIR);
	i = 0;
	while (mini->path_tab[i])
	{
		mini->comand = ft_strjoin_with_c(mini->path_tab[i], cur_cmd->args[0],
				'/');
		if (!mini->comand)
		{
			mini->fatal_error = 1;
			return (err_printf("%s", ERR_MSG_MALLOC, NULL, NULL), EXIT_FAILURE);
		}
		if (!is_dir(mini->comand) && !access(mini->comand, F_OK)
			&& !access(mini->comand, X_OK) && !access(mini->comand, R_OK))
			break ;
		free(mini->comand);
		mini->comand = NULL;
		i++;
	}
	if (mini->comand == NULL || cur_cmd->args[0][0] == '\0')
		print_exec_error(mini, cur_cmd->args[0], ERR_MSG_CMD);
	return (EXIT_SUCCESS);
}

void	set_absolute_command(t_cmd *cur_cmd, t_mini *mini)
{
	mini->comand = ft_strdup(cur_cmd->args[0]);
	if (!mini->comand)
		exit(free_everything(mini, 1));
	if (is_dir(mini->comand) == 1)
	{
		err_printf("%s%s%s", ERR_MSG_JM, cur_cmd->args[0], ERR_MSG_DIR);
		exit(free_everything(mini, 126));
	}
	if (access(mini->comand, F_OK))
	{
		err_printf("%s%s%s", ERR_MSG_JM, cur_cmd->args[0], ERR_MSG_FIDIR);
		exit(free_everything(mini, 127));
	}
	else if (access(mini->comand, X_OK) || access(mini->comand, R_OK))
	{
		err_printf("%s%s%s", ERR_MSG_JM, cur_cmd->args[0], ERR_MSG_PERM);
		exit(free_everything(mini, 126));
	}
}

int	execute(t_cmd *cur_cmd, t_mini *mini, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (cur_cmd->next != NULL && mini->fd_outfile < 3)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(mini->save_stdin);
	close(mini->save_stdout);
	if (!cur_cmd->args)
		exit(subshell_magik(cur_cmd, mini));
	remove_hd_list(&mini->heredocs);
	if (cur_cmd->args[0] == 0)
		exit(free_everything(mini, EXIT_SUCCESS));
	if (!ft_strnstr(cur_cmd->args[0], "/", ft_strlen(cur_cmd->args[0])))
		set_simple_command(cur_cmd, mini);
	else
		set_absolute_command(cur_cmd, mini);
	if (mini->fatal_error != 1 && execve(mini->comand, cur_cmd->args,
			mini->env) == -1)
		exit(free_everything(mini, 127));
	return (EXIT_FAILURE);
}
