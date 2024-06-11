/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:29:57 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/03 15:56:52 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t	g_global;

int	close_all_in_child(t_mini *mini, int *pipe_fd, int heredoc_fd, int value)
{
	if (heredoc_fd >= 0)
		close(heredoc_fd);
	if (pipe_fd[0] >= 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] >= 0)
		close(pipe_fd[1]);
	return (free_everything(mini, value));
}

void	prompt_gnl(int istty, char *line, int fd)
{
	if (istty)
		write(STDOUT_FILENO, ">", 1);
	if (line)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

int	process_final_line(char *line, t_mini *mini, char *limiter)
{
	if (line == NULL && g_global)
	{
		g_global = 0;
		mini->exit_status = 130;
		printf("\n");
		dup2(mini->save_stdin, STDIN_FILENO);
		return (E_STATUS_SIGINT);
	}
	else if (line == NULL && err_printf_fd_hd("%s %d %s%s%s",
			(char *[4]){ERR_MSG_HD1, ERR_MSG_HD2, limiter, "')\n"},
		mini->line_count) == -1)
		return (EXIT_FAILURE);
	else
		free(line);
	return (EXIT_SUCCESS);
}

void	trim_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = str[i + 1];
}

void	dollar_trimmer(char *str)
{
	int		i;
	char	isquote;

	isquote = 0;
	i = 0;
	while (str[i])
	{
		if (!isquote && str[i] == '$' && (ft_is_quote(str[i + 1])))
		{
			if (i != 0 && str[i - 1] != '$')
				trim_dollar(&str[i]);
			else
				i++;
		}
		else if (str[i] == '\'' || str[i] == '"')
		{
			if (!isquote)
				isquote = str[i];
			else if (isquote == str[i])
				isquote = 0;
			i++;
		}
		else
			i++;
	}
}
