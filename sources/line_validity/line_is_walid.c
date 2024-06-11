/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_is_walid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:23:52 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 15:08:46 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	line_is_walid(t_split **first, int *open_par, t_mini *mini, int open_hd)
{
	t_split	*current;

	current = *first;
	if (!current && *open_par == 0)
		return (EXIT_SUCCESS);
	else if (!current)
		return (syntax_err_msg_par_open(SYNTAX_ERR_PAR_OPEN, "(", NULL,
				open_hd));
	else if (current->tok_type == PIPE)
		return (line_is_walid_pipe(first, open_par, mini, open_hd));
	else if (current->sub_tok_type == REDIR)
		return (line_is_walid_redir(first, open_par, mini, open_hd));
	else if (current->sub_tok_type == CMD_END)
		return (line_is_walid_cmd_end(first, open_par, mini, open_hd));
	else if (current->tok_type == PAR_OPEN)
		return (line_is_walid_par_open(first, open_par, mini, open_hd));
	else if (current->tok_type == PAR_CLOSE)
		return (line_is_walid_par_close(first, open_par, mini, open_hd));
	else
		return (line_is_walid_cmd(first, open_par, mini, open_hd));
}

int	line_is_walid_pipe(t_split **first, int *open_par, t_mini *mini,
		int open_hd)
{
	t_split	*current;
	char	*next;

	next = NULL;
	current = *first;
	if (current->next)
		next = current->next->str;
	if (!current->next || !(current->next->sub_tok_type == CMD
			|| current->next->sub_tok_type == REDIR
			|| current->next->tok_type == PAR_OPEN))
		return (syntax_err_msg(get_syntax_err_value(current), current->str,
				next, open_hd));
	return (line_is_walid(&current->next, open_par, mini, open_hd));
}

int	check_first_token(t_split *first, int *exit_status, int open_hd)
{
	t_tok_type	type;

	type = first->tok_type;
	if (type == HD || type == OUTF_TRUNC || type == OUTF_APPEND || type == CMD
		|| type == INF || type == PAR_OPEN)
		return (EXIT_SUCCESS);
	else
	{
		*exit_status = SYNTAX_ERR;
		return (syntax_err_msg(SYNTAX_ERR, NULL, first->str, open_hd));
	}
}

int	get_syntax_err_value(t_split *current)
{
	if (current->sub_tok_type == INF)
		return (SYNTAX_ERR_INFILE);
	else if (current->sub_tok_type == HD)
		return (SYNTAX_ERR_HD);
	else if (current->sub_tok_type == OUTF_APPEND)
		return (SYNTAX_ERR_OUTF_APP);
	else if (current->sub_tok_type == OUTF_TRUNC)
		return (SYNTAX_ERR_OUTF_TRUNC);
	else if (current->sub_tok_type == AND)
		return (SYNTAX_ERR_AND);
	else if (current->sub_tok_type == OR)
		return (SYNTAX_ERR_OR);
	else
		return (SYNTAX_ERR_PIPE);
}

char	line_is_walid_quotes(char *line)
{
	char	is_quote;

	is_quote = 0;
	while (*line)
	{
		if ((*line == '\'' || *line == '\"') && is_quote == 0)
			is_quote = *line;
		else if ((*line == '\'' || *line == '\"') && is_quote == *line)
			is_quote = 0;
		line++;
	}
	return (is_quote);
}
