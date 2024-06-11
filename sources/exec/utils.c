/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:07:22 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/28 09:14:06 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_mini_struct(t_mini *mini, char **envp)
{
	mini->fd_infile = STDIN_FILENO;
	mini->fd_outfile = STDOUT_FILENO;
	mini->expand_heredoc = 1;
	mini->save_stdout = -1;
	mini->save_stdin = -1;
	if (isatty(STDIN_FILENO))
		mini->is_tty = 1;
	mini->fatal_error = errno;
	if (mini->fatal_error == EBADF)
		return (EXIT_FAILURE);
	mini->fatal_error = 0;
	if (get_envp(envp, &mini->env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!mini->env[0])
	{
		if (set_hiden_env(mini) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	mini->save_stdin = dup(STDIN_FILENO);
	if (mini->save_stdin < 0)
		return (EXIT_FAILURE);
	mini->save_stdout = dup(STDOUT_FILENO);
	if (mini->save_stdout < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_le_xav(char **dest)
{
	size_t	i;

	i = 0;
	if (!dest)
		return ;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

char	*get_env_variable(char **env, char *variable)
{
	int	i;
	int	len_to_equal;

	i = 0;
	while (env[i])
	{
		len_to_equal = ft_strlen_to_c(env[i], '=');
		if (len_to_equal)
		{
			if (env[i][len_to_equal] == '\0'
				&& ft_strcmp(variable, env[i]) == 0)
				return (env[i] + len_to_equal);
			env[i][len_to_equal] = 0;
			if (ft_strcmp(variable, env[i]) == 0)
			{
				env[i][len_to_equal] = '=';
				return (env[i] + len_to_equal + 1);
			}
			env[i][len_to_equal] = '=';
		}
		i++;
	}
	return (NULL);
}

char	*get_env_variable_2(char **env, char *variable, t_mini *mini)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(variable, env[i], ft_strlen_to_c(variable, '=')) == 0)
			return (env[i] + (ft_strlen_to_c(env[i], '=') + 1));
		i++;
	}
	if (ft_strcmp(variable, "PATH=") == 0)
		mini->is_path_empty = 1;
	return (NULL);
}
