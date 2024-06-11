/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:16:53 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 16:49:12 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_global_validity(t_mini *mini, t_split **parsed_line,
		int validity)
{
	int	parenthesis;

	parenthesis = 0;
	line_is_walid(parsed_line, &parenthesis, mini, 0);
	parenthesis = 0;
	validity = line_is_walid(parsed_line, &parenthesis, mini, 1);
	if (validity && validity != EXIT_FAILURE && validity != E_STATUS_SIGINT)
	{
		mini->exit_status = SYNTAX_ERR;
		remove_hd_list(&mini->heredocs);
		return (destroy_split_list(parsed_line, EXIT_SUCCESS));
	}
	else if (validity == EXIT_FAILURE)
	{
		remove_hd_list(&mini->heredocs);
		return (destroy_split_list(parsed_line, EXIT_FAILURE));
	}
	else if (validity == E_STATUS_SIGINT)
	{
		mini->exit_status = 130;
		return (remove_hd_list(&mini->heredocs), destroy_split_list(parsed_line,
				EXIT_SUCCESS));
	}
	return (EXIT_SUCCESS);
}

int	process_line(char *line, t_mini *mini)
{
	int	validity;

	validity = 0;
	mini->split_list = NULL;
	if (quote_validity(line, &mini->exit_status))
		return (EXIT_SUCCESS);
	if (line_parser(line, &mini->split_list) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	add_token_types(&mini->split_list);
	if (check_first_token(mini->split_list, &mini->exit_status,
			0) != EXIT_SUCCESS)
		return (destroy_split_list(&mini->split_list, EXIT_SUCCESS));
	if (check_global_validity(mini, &mini->split_list,
			validity) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!mini->split_list)
		return (EXIT_SUCCESS);
	if (create_tree(&mini->ast, &mini->split_list) == EXIT_FAILURE)
		return (remove_hd_list(&mini->heredocs), EXIT_FAILURE);
	if (select_node(mini->ast, mini) == EXIT_FAILURE)
		return (remove_hd_list(&mini->heredocs), destroy_tree(&mini->ast,
				EXIT_FAILURE));
	return (remove_hd_list(&mini->heredocs), destroy_tree(&mini->ast,
			EXIT_SUCCESS));
}

int	check_after_subshell_syntax(t_split *first, int open_hd)
{
	t_split	*current;

	current = first;
	while (current)
	{
		if (current->sub_tok_type == REDIR)
		{
			if (!current->next)
				return (EXIT_SUCCESS);
			current = current->next->next;
		}
		else if (current->sub_tok_type == CMD_END
			|| current->tok_type == PAR_CLOSE)
			return (EXIT_SUCCESS);
		else
			return (syntax_err_msg(SYNTAX_ERR_PAR_CLOSE, current->str,
					current->str, !open_hd));
	}
	return (EXIT_SUCCESS);
}
