/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:06:53 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/27 21:38:34 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strdup2(const char *s, char **dest)
{
	char	*dup;
	int		i;

	i = 0;
	if (s == NULL)
	{
		dup = (char *)malloc(sizeof(char));
		if (!dup)
			return (EXIT_FAILURE);
		dup[0] = 0;
		return (*dest = dup, EXIT_SUCCESS);
	}
	while (s[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (EXIT_FAILURE);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (*dest = dup, EXIT_SUCCESS);
}
