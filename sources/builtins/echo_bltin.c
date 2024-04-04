/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:16:23 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/04 11:56:26 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	writting(char *to_write)
{
	if (write(1, to_write, ft_strlen(to_write)) == -1)
	{
		strerror(errno);
		return (-1);
	}
	return (0);
}

static void	print_new_line(void)
{
	if (write(1, "\n", 1) == -1)
	{
		strerror(errno);
		return ;
	}
}

void	echo_bltin_v1(char *option, char *to_print)
{
	if (option)
	{
		if (ft_strcmp(option, "-n") == 0)
		{
			writting(to_print);
			return ;
		}
		else
		{
			if (writting(option) == -1)
				return ;
			if (!to_print)
				return (print_new_line());
			else
			{
				if (writting(" ") == -1)
					return ;
				if (writting(to_print) == -1)
					return ;
				print_new_line();
			}
		}
	}
}
