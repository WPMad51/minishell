/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:19:45 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/05 08:00:51 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_file_error(t_file *cur_file, t_mini *mini)
{
	if (access(cur_file->file_name, F_OK) == -1)
	{
		err_printf("%s%s%s", ERR_MSG_JM, cur_file->file_name, ERR_MSG_FIDIR);
	}
	else if (access(cur_file->file_name, F_OK | R_OK) == -1
		&& cur_file->redir_type == INFILE)
	{
		err_printf("%s%s%s", ERR_MSG_JM, cur_file->file_name, ERR_MSG_PERM);
	}
	else if (access(cur_file->file_name, F_OK | W_OK) == -1
		&& (cur_file->redir_type == OUTFILE_APPEND
			|| cur_file->redir_type == OUTFILE_TRUNC))
	{
		err_printf("%s%s%s", ERR_MSG_JM, cur_file->file_name, ERR_MSG_PERM);
	}
	else
	{
		if (is_dir(cur_file->file_name) == 1)
			err_printf("%s%s%s", ERR_MSG_JM, cur_file->file_name, ERR_MSG_DIR);
		else
			err_printf_plus("%s%s%s%s%s", (char *[5]){ERR_MSG_JM,
				cur_file->file_name, ERR_MSG_CANNOT, cur_file->file_name,
				ERR_MSG_TOO_MANY}, 5);
	}
	mini->file_error = 1;
}
