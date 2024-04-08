/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:51:40 by cdutel            #+#    #+#             */
/*   Updated: 2024/04/08 14:52:56 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define MAX_SIZE 4096

/*Builtins*/
char	**unset_bltin(char **envp, char *to_unset);
char	**export_bltin(char **envp, char *to_add);
void	env_bltin(char **envp);
void	pwd_bltin(void);

void	echo_bltin_v1(char *to_print, char *no_new_line);

void	cd_bltin(char *dir);
/*Utils*/
void	ft_le_xav(char **dest);

#endif
