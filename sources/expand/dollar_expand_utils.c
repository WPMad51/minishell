/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:53:36 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/21 15:20:41 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i++] == '$')
			return (1);
	}
	return (0);
}

t_expand	*create_new_expand(char *str, int i)
{
	t_expand	*output;

	output = malloc(sizeof(t_expand));
	if (!output)
		return (NULL);
	output->str = ft_strndup(str, i);
	if (!output->str)
	{
		free(output);
		return (NULL);
	}
	output->next = NULL;
	return (output);
}

void	get_str_output(char **str, int *i, int type)
{
	if (type == 1)
	{
		*str = malloc(sizeof(char) * 2);
		if (*str == NULL)
			return ;
		**str = '$';
		*(*str + 1) = 0;
		*i += 1;
	}
	else
	{
		*str = malloc(sizeof(char) * 1);
		if (str == NULL)
			return ;
		*str[0] = 0;
	}
	if (type == 3)
		*i += 1;
	else if (type == 2)
		*i += 2;
}

void	get_str_output_env(char *entry, char **str, int *i, char **envp)
{
	int		index;
	char	*var;

	index = 1;
	while (is_valid_env_char(entry[index + *i]))
		index++;
	var = ft_strndup(&entry[*i + 1], index - 1);
	if (var == NULL)
		return ;
	*str = ft_strdup(get_env_variable(envp, var));
	free(var);
	if (!(*str))
		return ;
	*i += index;
}

int	is_valid_env_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}
