/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:03:20 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/03 15:54:42 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t	g_global;

void	signal_heredoc(int sig)
{
	g_global = sig;
	close(STDIN_FILENO);
}

int	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return (EXIT_SUCCESS);
}

void	rl_sigint(int sig)
{
	g_global = sig;
	close(STDIN_FILENO);
}

int	signal_ms(void)
{
	signal(SIGINT, rl_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	return (EXIT_SUCCESS);
}
