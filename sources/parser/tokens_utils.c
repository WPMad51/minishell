/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:01:14 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/06 20:34:36 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node_type	is_redir_token(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (INF);
	if (!ft_strcmp(str, "<<"))
		return (HD);
	if (!ft_strcmp(str, ">"))
		return (OUTF_TRUNC);
	if (!ft_strcmp(str, ">>"))
		return (OUTF_APPEND);
	return (0);
}

t_node_type	is_cmd_end_token(char *str)
{
	if (!ft_strcmp(str, "&&"))
		return (AND);
	if (!ft_strcmp(str, "||"))
		return (OR);
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	return (0);
}

t_node_type	is_par(char *str)
{
	if (!ft_strcmp(str, "("))
		return (PAR_OPEN);
	if (!ft_strcmp(str, ")"))
		return (PAR_CLOSE);
	return (0);
}

t_node_type	is_word(char *str)
{
	if (!(is_cmd_end_token(str) || is_par(str) || is_redir_token(str)))
		return (CMD);
	return (0);
}

int	is_token(char *str)
{
	if (!ft_strncmp("&&", str, 2) || !ft_strncmp("||", str, 2)
		|| !ft_strncmp(">>", str, 2) || !ft_strncmp("<<", str, 2))
		return (2);
	else if (!ft_strncmp("<", str, 1) || !ft_strncmp(">", str, 1)
		|| !ft_strncmp("|", str, 1) || !ft_strncmp("(", str, 1)
		|| !ft_strncmp(")", str, 1))
		return (1);
	return (0);
}
