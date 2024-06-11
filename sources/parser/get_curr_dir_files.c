/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curr_dir_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:03:19 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 15:08:16 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	gf_add_file_and_type(t_dir **first, struct dirent *files, DIR *dir_fd,
		char *is_dir)
{
	if (addback_dir_list(first, files->d_name) == EXIT_FAILURE)
	{
		closedir(dir_fd);
		destroy_dir_list(first);
		return (EXIT_FAILURE);
	}
	is_dir[0] = (char)files->d_type;
	if (addback_dir_list(first, is_dir) == EXIT_FAILURE)
	{
		closedir(dir_fd);
		destroy_dir_list(first);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	gf_roll_through_files(t_dir **first, DIR *dir_fd, char *is_dir)
{
	struct dirent	*files;

	errno = 0;
	files = readdir(dir_fd);
	while (files)
	{
		if (gf_add_file_and_type(first, files, dir_fd, is_dir) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		files = readdir(dir_fd);
	}
	if (errno)
	{
		closedir(dir_fd);
		destroy_dir_list(first);
		return (EXIT_FAILURE);
	}
	closedir(dir_fd);
	return (EXIT_SUCCESS);
}

int	gf_check_dir_content(char ***dir_content, char *dir_name)
{
	DIR		*dir_fd;
	char	*is_dir;
	t_dir	*first;

	first = NULL;
	dir_fd = opendir(dir_name);
	if (dir_fd == NULL)
		return (free(dir_name), EXIT_SUCCESS);
	free(dir_name);
	is_dir = malloc(2);
	if (!is_dir)
		return (closedir(dir_fd), EXIT_FAILURE);
	ft_bzero(is_dir, sizeof(char) * 2);
	if (gf_roll_through_files(&first, dir_fd, is_dir) == EXIT_FAILURE)
		return (free(is_dir), EXIT_FAILURE);
	free(is_dir);
	return (process_dir_list(&first, dir_content));
}

int	get_files(char ***dir_content)
{
	char	*wd;
	int		value;

	value = get_curr_dir_name(&wd, 0);
	if (value == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (value == ERR_GETCWD)
		return (EXIT_SUCCESS);
	return (gf_check_dir_content(dir_content, wd));
}

int	process_dir_list(t_dir **first, char ***output)
{
	t_dir	*current;
	int		count;

	current = *first;
	count = 0;
	while (current)
	{
		current = current->next;
		count++;
	}
	(*output) = malloc(sizeof(char *) * (count + 1));
	if (!(*output))
		return (destroy_dir_list(first), EXIT_FAILURE);
	ft_bzero((*output), sizeof(char *) * (count + 1));
	current = *first;
	count = 0;
	while (current)
	{
		(*output)[count] = ft_strdup(current->name);
		if ((*output)[count++] == NULL)
			return (destroy_dir_list(first), destroy_tab(output), EXIT_FAILURE);
		current = current->next;
	}
	return (destroy_dir_list(first), EXIT_SUCCESS);
}
