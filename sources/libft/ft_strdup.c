/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:06:53 by cdutel            #+#    #+#             */
/*   Updated: 2024/05/09 16:32:53 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*output;

	output = malloc(sizeof(char) * (n + 1));
	if (!output)
		return (NULL);
	output[n] = 0;
	while (n)
	{
		output[n - 1] = str[n - 1];
		n--;
	}
	return (output);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	if (s == NULL)
	{
		dup = (char *)malloc(sizeof(char));
		if (!dup)
			return (NULL);
		dup[0] = 0;
		return (dup);
	}
	while (s[i])
		i++;
	dup = (char *)malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
