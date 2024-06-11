/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:35:14 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 16:51:46 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_global;

void	ft_sleep(double n)
{
	double	i;

	i = 0.0;
	while (i++ < n * 100000000)
		;
}

static void	print_intro(void)
{
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	printf("\033[%d;%dH", 0, 0);
	if (INTRO)
	{
		ft_sleep(1);
		printf(ART2);
		ft_sleep(1);
		printf(ART3);
		ft_sleep(1);
		printf(ART4);
		ft_sleep(1);
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("\n\n\n\n\n\n\n\n\n\n\n");
		printf("\033[%d;%dH", 0, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		exit_status;
	t_mini	mini;

	(void)ac;
	(void)av;
	ft_bzero(&mini, sizeof(t_mini));
	if (init_mini_struct(&mini, envp) == EXIT_FAILURE)
		return (free_everything(&mini, ERR_INIT));
	signal_ms();
	if ((mini.is_tty && !DEBUG_TTY) || DEBUG_RL)
	{
		print_intro();
		exit_status = readline_loop(&mini, PROMPT_RL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		exit_status = gnl_loop(&mini);
	}
	mini.line = NULL;
	if (!exit_status)
		exit_status = mini.exit_status;
	return (free_everything(&mini, exit_status));
}
