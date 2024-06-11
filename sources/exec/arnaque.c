/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arnaque.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:11:26 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/29 08:55:04 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	err_printf(char *input_printf, char *str2, char *str3, char *str4)
{
	int	output;
	int	duplicate;

	duplicate = dup(STDOUT_FILENO);
	if (duplicate < 0)
		return (-1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (str4)
		output = printf(input_printf, str2, str3, str4);
	else if (str3)
		output = printf(input_printf, str2, str3);
	else
		output = printf(input_printf, str2);
	dup2(duplicate, STDOUT_FILENO);
	close(duplicate);
	return (output);
}

int	err_printf_plus(char *input_printf, char **strs, int size)
{
	int	duplicate;
	int	output;

	duplicate = dup(STDOUT_FILENO);
	if (duplicate < 0)
		return (-1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (size == 4)
		output = printf(input_printf, strs[0], strs[1], strs[2], strs[3]);
	else if (size == 5)
		output = printf(input_printf, strs[0], strs[1], strs[2], strs[3],
				strs[4]);
	else if (size == 6)
		output = printf(input_printf, strs[0], strs[1], strs[2], strs[3],
				strs[4], strs[5]);
	else if (size == 7)
		output = printf(input_printf, strs[0], strs[1], strs[2], strs[3],
				strs[4], strs[5], strs[6]);
	else
		output = -1;
	dup2(duplicate, STDOUT_FILENO);
	close(duplicate);
	return (output);
}

int	err_printf_fd_hd(char *printf_prompt, char **strs, int line_count)
{
	int	output;
	int	duplicate;

	duplicate = dup(STDOUT_FILENO);
	if (duplicate < 0)
		return (-1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	output = printf(printf_prompt, strs[0], line_count, strs[1], strs[2],
			strs[3]);
	dup2(duplicate, STDOUT_FILENO);
	close(duplicate);
	return (output);
}

int	err_printf_quote(char *printf_prompt, char c)
{
	int	output;
	int	duplicate;

	duplicate = dup(STDOUT_FILENO);
	if (duplicate < 0)
		return (-1);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	output = printf(printf_prompt, c);
	dup2(duplicate, STDOUT_FILENO);
	close(duplicate);
	return (output);
}
