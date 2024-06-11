/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:11:47 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 13:44:13 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t	g_global;

int	process_empty_line(t_mini *mini)
{
	if (!g_global)
	{
		printf("exit\n");
		return (mini->exit_status);
	}
	if (mini->exit_status != 130 || mini->last_exit_signaled)
	{
		printf("\n");
		mini->last_exit_signaled = 0;
	}
	g_global = 0;
	mini->exit_status = 130;
	dup2(mini->save_stdin, STDIN_FILENO);
	return (readline_loop(mini, PROMPT_RL_ERR));
}

void	loop_beginning_rl(char **line, char **prompt, t_mini *mini)
{
	mini->line_count++;
	free(*line);
	if (!mini->exit_status)
		*prompt = PROMPT_RL;
	*line = readline(*prompt);
}

int	readline_loop(t_mini *mini, char *prompt)
{
	int		val;

	val = 0;
	while (1)
	{
		loop_beginning_rl(&mini->line, &prompt, mini);
		if (mini->line == NULL)
			return (process_empty_line(mini));
		if (!only_space(mini->line))
		{
			val = process_line(mini->line, mini);
			if (val)
				return (free(mini->line), val);
			if (mini->line[0])
				add_history(mini->line);
			if (mini->exit_status)
				return (readline_loop(mini, PROMPT_RL_ERR));
		}
	}
	free(mini->line);
	return (mini->exit_status);
}
