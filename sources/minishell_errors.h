/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdutel <cdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:38:36 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/05 08:00:46 by cdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERRORS_H
# define MINISHELL_ERRORS_H
# define ERR_INIT 1
# define ERR_GETCWD 2
# define E_STATUS_SIGINT 130
# define SYNTAX_OK 0
# define SYNTAX_ERR 2
# define SYNTAX_ERR_PAR_OPEN 2
# define SYNTAX_ERR_PAR_CLOSE 2
# define SYNTAX_ERR_AND 2
# define SYNTAX_ERR_OR 6
# define SYNTAX_ERR_PIPE 2
# define SYNTAX_ERR_REDIR 3
# define SYNTAX_ERR_HD 2
# define SYNTAX_ERR_INFILE 2
# define SYNTAX_ERR_OUTF_TRUNC 2
# define SYNTAX_ERR_OUTF_APP 2
# define SYNTAX_ERR_QUOTE 2
# define SYNTAX_ERR_DQUOTE 2
# define ERR_OP_FILE 2
/*ERR_MSG*/
# define ERR_MSG_HD1 "mishell del 🍑: warning: here-document at line"
# define ERR_MSG_HD2 "delimited by end-of-file (wanted `"
# define ERR_MSG_QUOTE "mishell del 🍑: unexpected newline\
 while looking for matching `%c'\n"
# define ERR_MSG_PIPE "Error with pipe\n"
# define ERR_MSG_FORK "Error with fork\n"
# define ERR_MSG_MALLOC "mishell del 🍑: Cannot allocate memory\n"
# define ERR_MSG_SYNTAX "mishell del 🍑: Syntax error\n"
# define ERR_MSG_JM "mishell del 🍑: "
# define ERR_MSG_FIDIR ": No such file or directory\n"
# define ERR_MSG_DIR ": Is a directory\n"
# define ERR_MSG_CMD ": command not found\n"
# define ERR_MSG_PERM ": Permission denied\n"
# define ERR_MSG_GET_FILES "mishell del 🍑: get_files: Cannot allocate memory\n"
# define ERR_MSG_EXPAND_NODES "mishell del 🍑: expand_nodes:\
Cannot allocate memory\n"
# define ERR_MSG_GET_ENVP "mishell del 🍑: get_envp: Cannot allocate memory\n"
# define ERR_MSG_CANNOT ": cannot create "
# define ERR_MSG_TOO_MANY ": Too many open files\n"
/*ERR_MSG_BUILTINS*/
# define ERR_MSG_CD "mishell del 🍑: cd: "
# define ERR_MSG_CD_ARG "mishell del 🍑: cd: too many arguments\n"
# define ERR_MSG_CD_FATAL_ERR "mishell del 🍑: cd: Cannot allocate memory\n"
# define ERR_MSG_CD_HOME "mishell del 🍑: cd: HOME not set\n"
# define ERR_MSG_CD_OLD "mishell del 🍑: cd: OLDPWD not set\n"
# define ERR_MSG_ECHO_WRITE "mishell del 🍑: echo: write error"
# define ERR_MSG_ENV_WRITE "env: write error"
# define ERR_MSG_EXIT "mishell del 🍑: exit: "
# define ERR_MSG_EXIT_NUM ": numeric argument required\n"
# define ERR_MSG_EXIT_ARG "mishell del 🍑: exit: too many arguments\n"
# define ERR_MSG_EXPORT "mishell del 🍑: export: '"
# define ERR_MSG_EXPORT_ID "': not a valid identifier\n"
# define ERR_MSG_EXPORT_OP "': invalid option\n"
# define ERR_MSG_EXPORT_WRITE "mishell del 🍑: export: write error"
# define ERR_MSG_EXPORT_FAT_ERR "mishell del 🍑: export\
: Cannot allocate memory\n"
# define ERR_MSG_PWD "pwd: cannot determine working directory :\
getcwd : cannot access parent directory"
# define ERR_MSG_PWD_2 "mishell del 🍑: pwd: "
# define ERR_MSG_PWD_OP ": invalid option\n"
# define ERR_MSG_PWD_FAT_ERR "mishell del 🍑: pwd: Cannot allocate memory\n"
# define ERR_MSG_PWD_WRITE "mishell del 🍑: pwd: write error"
# define ERR_MSG_UNSET_FAT_ERR "mishell del 🍑: unset: Cannot allocate memory\n"

# define ENV_I_PATH "/home/cdutel/.local/funcheck/host:/home/cdutel/bin:\
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:\
/usr/local/games:/snap/bin"
#endif
