/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:02:51 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 15:07:03 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_err_msg(int err_value, char *current_token, char *token, int open_hd)
{
	if (open_hd)
		return (err_value);
	if (token == NULL)
	{
		token = "newline";
	}
	if (err_value == SYNTAX_ERR_REDIR)
		err_printf("mishell del 🍑: %s: ambiguous redirect\n", current_token,
			NULL, NULL);
	else
		err_printf("mishell del 🍑: syntax error near unexpected token `%s'\n",
			token, NULL, NULL);
	return (err_value);
}

int	syntax_err_msg_par_open(int err_value, char *current_token, char *token,
		int open_hd)
{
	(void)token;
	if (open_hd)
		return (err_value);
	err_printf("mishell del 🍑: unexpected \
	newline while looking for matching `%s'\n",
		current_token, NULL, NULL);
	return (err_value);
}
