/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bltin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:16:40 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/03 18:48:57 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_pwd_error(t_mini *mini, int is_child, char *pathname)
{
	perror(ERR_MSG_PWD_WRITE);
	mini->exit_status = 1;
	free(pathname);
	if (is_child == 1)
		(exit(1));
	return (EXIT_SUCCESS);
}

static int	check_option(t_mini *mini, char **args, int is_child)
{
	int	i;
	int	less;

	i = 0;
	less = 0;
	while (args[1][i])
	{
		if (args[1][i] == '-')
			less++;
		i++;
	}
	if (less == 2 && i == 2)
		return (0);
	else if (less > 0)
	{
		err_printf("%s%s%s", ERR_MSG_PWD_2, args[1], ERR_MSG_PWD_OP);
		if (is_child == 1)
			exit(2);
		mini->exit_status = 2;
		return (1);
	}
	return (0);
}

static int	err_value(t_mini *mini, int is_child)
{
	mini->exit_status = 1;
	if (is_child == 1)
		exit(1);
	return (EXIT_SUCCESS);
}

int	pwd_bltin(t_mini *mini, char **args, int is_child)
{
	char	*pathname;
	int		err_val;

	pathname = NULL;
	if (args[1] != NULL && check_option(mini, args, is_child) == 1)
		return (EXIT_SUCCESS);
	err_val = get_curr_dir_name(&pathname, 1);
	if (err_val == EXIT_FAILURE)
	{
		free_on_failure(mini);
		return (err_printf("%s", ERR_MSG_PWD_FAT_ERR, NULL, NULL),
			EXIT_FAILURE);
	}
	else if (err_val == ERR_GETCWD)
		return (err_value(mini, is_child));
	if (printf("%s\n", pathname) == -1)
		return (print_pwd_error(mini, is_child, pathname));
	free(pathname);
	mini->exit_status = 0;
	if (is_child == 1)
		exit(0);
	return (EXIT_SUCCESS);
}

int	get_curr_dir_name(char **pathname, int print_err_msg)
{
	char	*wd;
	int		size;

	size = 128;
	wd = malloc(sizeof(char) * size);
	if (!wd)
		return (EXIT_FAILURE);
	while (!getcwd(wd, size))
	{
		if (errno != ERANGE)
		{
			if (print_err_msg)
				perror(ERR_MSG_PWD);
			return (free(wd), ERR_GETCWD);
		}
		free(wd);
		size += 128;
		wd = malloc(sizeof(char) * size);
		if (!wd)
			return (EXIT_FAILURE);
	}
	*pathname = wd;
	return (EXIT_SUCCESS);
}
