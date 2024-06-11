/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:44:27 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/20 13:39:57 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_wildcard_dir(char *wild)
{
	int	i;

	i = 0;
	while (wild[i])
		i++;
	while (i && wild[i - 1] == '*')
		i--;
	if ((i && wild[i - 1] != '/') || !i)
		return (0);
	while (i)
	{
		if ((wild[i - 1] == '.' && wild[i] == '/') || wild[i - 1] == '/')
			i--;
		else
			break ;
	}
	return (i);
}

// int main(int ac, char**av)
// {
//     (void)ac;
//     int i = is_wildcard_dir(av[1]);
//     printf("before %s\n", av[1]);
//     av[1][i] = 0;
//     printf("after %s\n", av[1]);
//     return (0);
// }
