/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:46:08 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 15:06:02 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	process_result(t_split **tok_with_w, t_split *wildcard)
{
	t_split	*tmp_next;
	t_split	*tmp_wildcard;

	if (!wildcard)
	{
		quote_trimmer((*tok_with_w)->str);
		return ;
	}
	tmp_next = (*tok_with_w)->next;
	free((*tok_with_w)->str);
	(*tok_with_w)->str = wildcard->str;
	tmp_wildcard = wildcard;
	if (tmp_wildcard->next != NULL)
	{
		(*tok_with_w)->next = tmp_wildcard->next;
		while (tmp_wildcard->next)
			tmp_wildcard = tmp_wildcard->next;
		tmp_wildcard->next = tmp_next;
	}
	free(wildcard);
}

int	expand_one_wildcard(t_split **tok_with_w, char **files)
{
	t_split	*wildcard;
	char	*trimmed_wild[3];

	wildcard = NULL;
	trimmed_wild[0] = NULL;
	trimmed_wild[2] = NULL;
	if (w_get_front_offset(&trimmed_wild[0],
			(*tok_with_w)->str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	trimmed_wild[1] = ft_strdup((*tok_with_w)->str
			+ ft_strlen(trimmed_wild[0]));
	if (!trimmed_wild[1])
		return (free(trimmed_wild[0]), EXIT_FAILURE);
	if (w_get_back_offset(&trimmed_wild[2], trimmed_wild[1]) == EXIT_FAILURE)
		return (free(trimmed_wild[0]), free(trimmed_wild[1]), EXIT_FAILURE);
	return (w_process_all(trimmed_wild, files, &wildcard, tok_with_w));
}

int	w_process_all(char **trim, char **files, t_split **wildcard_list,
		t_split **tok_with_w)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(trim[2]);
	while (files[2 * i])
	{
		if (wildcard_match(trim[1], files[2 * i]) && ((len && (int)files[2 * i
						+ 1][0] == DT_DIR) || len == 0))
		{
			tmp = get_wildcard_result(trim[0], files[2 * i], trim[2]);
			if (!tmp)
				return (w_free_trim(trim), destroy_split_list(wildcard_list,
						EXIT_FAILURE));
			if (add_back_wildcard_list(wildcard_list, tmp) == EXIT_FAILURE)
				return (w_free_trim(trim), free(tmp),
					destroy_split_list(wildcard_list, EXIT_FAILURE));
			free(tmp);
		}
		i++;
	}
	w_free_trim(trim);
	process_result(tok_with_w, *wildcard_list);
	return (EXIT_SUCCESS);
}

int	w_get_back_offset(char **result, char *wild)
{
	int	i;
	int	j;

	i = is_wildcard_dir(wild);
	j = 0;
	if (i)
	{
		while (wild[j])
			j++;
		while (wild[j - 1] == '*')
			j--;
		(*result) = ft_strndup(&wild[i], j - i);
		if (!(*result))
			return (EXIT_FAILURE);
		wild[i] = 0;
	}
	return (EXIT_SUCCESS);
}

int	w_get_front_offset(char **result, char *wild)
{
	int	i;

	i = 0;
	while (ft_strncmp(wild + i, "./", 2) == 0 || *(wild + i) == '/')
	{
		if (ft_strncmp(wild + i, "./", 2) == 0)
			i++;
		i++;
	}
	if (i)
	{
		(*result) = ft_strndup(wild, i);
		if (!(*result))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
