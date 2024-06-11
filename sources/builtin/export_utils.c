/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 01:36:56 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 07:45:31 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_equal(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	get_size(char *to_add, char *env_line)
{
	if (contains_equal(to_add) == 1 && contains_equal(env_line) == 1)
	{
		if (ft_strlen_to_c(to_add, '=') > ft_strlen_to_c(env_line, '='))
			return (ft_strlen_to_c(to_add, '='));
		return (ft_strlen_to_c(env_line, '='));
	}
	else if (contains_equal(to_add) == 1 && contains_equal(env_line) == 0)
	{
		if (ft_strlen_to_c(to_add, '=') > ft_strlen(env_line))
			return (ft_strlen_to_c(to_add, '='));
		return (ft_strlen(env_line));
	}
	else if (contains_equal(to_add) == 0 && contains_equal(env_line) == 1)
	{
		if (ft_strlen_to_c(env_line, '=') > ft_strlen(to_add))
			return (ft_strlen_to_c(env_line, '='));
		return (ft_strlen(to_add));
	}
	if (ft_strlen(to_add) > ft_strlen(env_line))
		return (ft_strlen(to_add));
	return (ft_strlen(env_line));
}

static int	is_valid_id(char *to_add, int i, int equal)
{
	if (i == 0 && to_add[i] == '=')
		return (1);
	else if (i == 0 && (to_add[i] >= '0' && to_add[i] <= '9'))
		return (1);
	else if (i == 0 && to_add[i] == '$' && (to_add[i + 1] == '\0'
			|| (equal == 0 && to_add[i + 1] == '\0')))
		return (1);
	else if (equal == 0)
	{
		if (!((to_add[i] >= 'A' && to_add[i] <= 'Z')
				|| (to_add[i] >= 'a' && to_add[i] <= 'z')
				|| (to_add[i] >= '0' && to_add[i] <= '9')
				|| (to_add[i] == '_')))
			return (1);
	}
	return (0);
}

int	check_to_add(t_mini *mini, char *to_add, int *trigger)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	if (to_add[i] == '\0')
	{
		*trigger = -1;
		err_printf("%s%s%s", ERR_MSG_EXPORT, to_add, ERR_MSG_EXPORT_ID);
		return (1);
	}
	while (to_add[i])
	{
		if (to_add[i] == '=' && equal == 0)
			equal = 1;
		if (is_valid_id(to_add, i, equal) == 1)
		{
			*trigger = -1;
			return (export_error(mini, to_add[i], to_add));
		}
		i++;
	}
	return (0);
}

int	export_error(t_mini *mini, int c, char *s)
{
	if (c == 0)
	{
		err_printf("%s", ERR_MSG_EXPORT_FAT_ERR, NULL, NULL);
		return (mini->fatal_error = 1, 1);
	}
	else if (c == '-')
	{
		err_printf("%s%s%s", ERR_MSG_EXPORT, s, ERR_MSG_EXPORT_OP);
		return (mini->exit_status = 2, 2);
	}
	else
	{
		err_printf("%s%s%s", ERR_MSG_EXPORT, s, ERR_MSG_EXPORT_ID);
		return (mini->exit_status = 1, 1);
	}
}
