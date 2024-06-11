/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:16:23 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 15:13:03 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_echo_error(t_mini *mini, int is_child)
{
	perror(ERR_MSG_ECHO_WRITE);
	mini->exit_status = 1;
	if (is_child == 1)
		(exit(free_everything(mini, 1)));
	return (EXIT_SUCCESS);
}

static int	valid_option(char *option)
{
	int	i;

	i = 1;
	if (!option || option[0] != '-')
		return (1);
	while (option[i])
	{
		if (option[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static int	check_option(char **arg, int *i)
{
	int	new_line;

	new_line = 1;
	while (arg[(*i)] && valid_option(arg[(*i)]) == 0)
	{
		new_line = 0;
		if (arg[(*i) + 1] == NULL)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	return (new_line);
}

int	echo_bltin(char **arg, t_mini *mini, int is_child)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = check_option(arg, &i);
	while (arg[i])
	{
		if (write(1, arg[i], ft_strlen(arg[i])) == -1)
			return (print_echo_error(mini, is_child));
		if (arg[i + 1] != NULL && write(1, " ", 1) == -1)
			return (print_echo_error(mini, is_child));
		i++;
	}
	if (new_line == 1 && write(1, "\n", 1) == -1)
		return (print_echo_error(mini, is_child));
	mini->exit_status = 0;
	if (is_child == 1)
		(exit(free_everything(mini, EXIT_SUCCESS)));
	return (EXIT_SUCCESS);
}
