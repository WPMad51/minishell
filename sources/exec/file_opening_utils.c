/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 08:39:45 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 08:42:20 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	printf_syntax_err(t_mini *mini, char *filename)
{
	mini->exit_status = 1;
	return (syntax_err_msg(SYNTAX_ERR_REDIR, filename,
			NULL, 0));
}
