/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_writing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:52:17 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/22 15:05:05 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	write_expanded_line(int fd, char *line, t_mini *mini, char need_exp)
{
	int	i;

	i = 0;
	if (!line)
		return (EXIT_SUCCESS);
	if (need_exp == 'a')
		return (write(fd, line, ft_strlen(line)), EXIT_SUCCESS);
	while (line[i])
	{
		if (line[i] == '$')
			write_env_var(&line[i], &i, fd, mini);
		else
			write(fd, &line[i++], 1);
	}
	return (EXIT_SUCCESS);
}

int	write_env_var(char *dolls, int *i, int fd, t_mini *mini)
{
	int	index;

	index = 1;
	if (!dolls[index] || (!is_valid_env_char(dolls[index])
			&& dolls[index] != '?'))
	{
		write(fd, "$", 1);
		*i += 1;
	}
	else if (is_valid_env_char(dolls[index]) && !ft_isdigit(dolls[index]))
	{
		if (print_var(&dolls[index], i, mini->env, fd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (dolls[index] == '?')
	{
		ft_putnbr_fd(mini->exit_status, fd);
		*i += 2;
	}
	else if (ft_isdigit(dolls[index]))
		*i += 2;
	return (EXIT_SUCCESS);
}

int	print_var(char *dolls, int *i, char **env, int fd)
{
	int		index;
	char	*var;
	char	*tmp;

	index = 0;
	while (is_valid_env_char(dolls[index]))
		index++;
	var = ft_strndup(dolls, index);
	if (!var)
		return (EXIT_FAILURE);
	tmp = get_env_variable(env, var);
	free(var);
	if (tmp)
		write(fd, tmp, ft_strlen(tmp));
	*i += index + 1;
	return (EXIT_SUCCESS);
}
