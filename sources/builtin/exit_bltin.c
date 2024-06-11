/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:44:30 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 13:47:27 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atolli(char *to_convert)
{
	int						sign;
	int						i;
	unsigned long long int	res;

	sign = 1;
	res = 0;
	i = 0;
	if (to_convert[i] == '+' || to_convert[i] == '-')
	{
		if (to_convert[i++] == '-')
			sign = -1;
	}
	while (to_convert[i])
	{
		if ((sign == 1 && res > LLMAX / 10) || (sign == -1 && res > LLMIN / 10))
			return (-1);
		res = res * 10 + (to_convert[i++] - '0');
		if ((sign == 1 && res > LLMAX) || (sign == -1 && res > LLMIN))
			return (-1);
	}
	if ((sign == -1 && res == LLMIN))
		return (0);
	if (sign == -1)
		return (256 - (res % 256));
	return (res % 256);
}

static int	is_only_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && (arg[i] == '-' || arg[i] == '+') && arg[i + 1] != '\0')
			i++;
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	case_only_num(t_mini *mini, int is_child, char **args)
{
	mini->exit_status = ft_atolli(args[1]);
	if (mini->exit_status == -1)
	{
		if (is_child == 0 && mini->is_subshell == 0)
			err_printf_plus("%s%s%s%s", (char *[4]){"exit\n", ERR_MSG_EXIT,
				args[1], ERR_MSG_EXIT_NUM}, 4);
		else
			err_printf("%s%s%s", ERR_MSG_EXIT, args[1], ERR_MSG_EXIT_NUM);
		mini->exit_status = 2;
		return (0);
	}
	if (args[2] == NULL && is_child == 0 && mini->is_subshell == 0)
		printf("exit\n");
	else if (args[2] != NULL)
	{
		if (is_child == 0 && mini->is_subshell == 0)
			err_printf("%s%s", "exit\n", ERR_MSG_EXIT_ARG, NULL);
		else
			err_printf("%s", ERR_MSG_EXIT_ARG, NULL, NULL);
		mini->exit_status = 1;
		return (1);
	}
	return (0);
}

static int	check_exit_validity(char **args, t_mini *mini, int is_child)
{
	if (is_only_num(args[1]) == 1)
	{
		if (is_child == 0 && mini->is_subshell == 0)
			err_printf_plus("%s%s%s%s", (char *[4]){"exit\n", ERR_MSG_EXIT,
				args[1], ERR_MSG_EXIT_NUM}, 4);
		else
			err_printf("%s%s%s", ERR_MSG_EXIT, args[1], ERR_MSG_EXIT_NUM);
		mini->exit_status = 2;
		return (0);
	}
	else
		return (case_only_num(mini, is_child, args));
	return (0);
}

int	exit_bltin(t_mini *mini, char **args, int is_child)
{
	if (args[1] == NULL)
	{
		if (is_child == 0 && mini->is_subshell == 0)
			printf("exit\n");
		free_everything(mini, mini->exit_status);
		exit(mini->exit_status);
	}
	if (check_exit_validity(args, mini, is_child) == 1)
	{
		if (is_child == 1)
		{
			free_everything(mini, mini->exit_status);
			exit(mini->exit_status);
		}
		return (EXIT_SUCCESS);
	}
	free_everything(mini, mini->exit_status);
	exit(mini->exit_status);
	return (EXIT_SUCCESS);
}
