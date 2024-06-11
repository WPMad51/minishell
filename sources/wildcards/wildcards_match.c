/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_match.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:34:47 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/20 13:35:47 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wildcard_match(char *wildcard, char *str)
{
	int	i;
	int	j;

	if (w_wildcard_match_start(wildcard, str, &i) == 0)
		return (0);
	j = i;
	if (!wildcard_loop(&wildcard[i], &str[j], &i, &j))
		return (0);
	return (w_wildcard_match_end(wildcard, str, i, j));
}

int	w_wildcard_match_start(char *wildcard, char *str, int *comp1)
{
	*comp1 = 0;
	if (str[0] == '.' && wildcard[0] != '.')
		return (0);
	while (wildcard[*comp1] && wildcard[*comp1] != '*')
		*comp1 += 1;
	if (*comp1 && ft_strncmp(wildcard, str, *comp1))
		return (0);
	return (1);
}

int	wildcard_loop(char *wildcard, char *str, int *i, int *j)
{
	int	comp_len;
	int	k;
	int	l;

	comp_len = 0;
	k = 0;
	l = 0;
	while (wildcard[k] == '*')
		k++;
	while (wildcard[comp_len + k] && wildcard[k + comp_len] != '*')
		comp_len++;
	*i += k;
	if (!wildcard[comp_len + k])
		return (1);
	while (str[l] && ft_strncmp(&wildcard[k], &str[l], comp_len))
		l++;
	k += comp_len;
	*i += comp_len;
	if (!str[l])
		return (0);
	l += comp_len;
	*j += l;
	return (wildcard_loop(&wildcard[k], &str[l], i, j));
}

int	w_wildcard_match_end(char *wildcard, char *str, int i, int j)
{
	int	comp1;
	int	comp2;

	comp1 = 0;
	while (wildcard[i + comp1])
		comp1++;
	if (!comp1)
		return (1);
	comp2 = 0;
	while (str[j + comp2])
		comp2++;
	if (comp2 < comp1)
		return (0);
	return (!ft_strcmp(&wildcard[i], &str[j + comp2 - comp1]));
}
