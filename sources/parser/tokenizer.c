/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:36:24 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/05/06 20:50:11 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token_types(t_split **first_elem)
{
	t_split	*current;

	current = *first_elem;
	if (!current)
		return ;
	while (current)
	{
		current->tok_type = get_tok_type(current->str);
		current->sub_tok_type = get_sub_tok_type(current->tok_type);
		current = current->next;
	}
}

t_tok_type	get_tok_type(char *str)
{
	t_tok_type	out;

	out = is_cmd_end_token(str);
	if (out)
		return (out);
	out = is_par(str);
	if (out)
		return (out);
	out = is_redir_token(str);
	if (out)
		return (out);
	return (CMD);
}

t_tok_type	get_sub_tok_type(t_tok_type type)
{
	if (type == PAR_CLOSE || type == PAR_OPEN)
		return (PAR);
	if (type == AND || type == OR || type == PIPE)
		return (CMD_END);
	if (type == INF || type == OUTF_APPEND || type == OUTF_TRUNC
		|| type == HD)
		return (REDIR);
	return (CMD);
}
