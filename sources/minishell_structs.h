/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:40:23 by dwayenbo          #+#    #+#             */
/*   Updated: 2024/06/04 13:43:12 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_node	t_node;
typedef struct s_proc	t_proc;
typedef struct s_split	t_split;
typedef struct s_heredocs
{
	int					fd;
	struct s_heredocs	*next;
}						t_heredocs;

typedef struct s_mini
{
	char				**env;
	char				**path_tab;
	char				**dir_list;
	char				*comand;
	char				*env_path;
	char				*path;
	char				*var_expanded;
	int					exit_status;
	int					last_exit_signaled;
	int					fd_infile;
	int					fd_outfile;
	int					file_error;
	int					fatal_error;
	int					is_env_i;
	int					is_path_empty;
	int					is_path_uns;
	int					is_pipe;
	int					last_pid;
	int					pid_num;
	int					save_stdin;
	int					save_stdout;
	int					status;
	int					infile_is_heredoc;
	int					expand_heredoc;
	int					line_count;
	int					is_tty;
	int					is_subshell;
	char				*line;
	t_proc				*processes;
	t_heredocs			*heredocs;
	t_node				*ast;
	t_split				*split_list;
}						t_mini;

struct					s_proc
{
	int					pid;
	t_proc				*next;
};

typedef struct s_dir
{
	struct s_dir		*next;
	char				*name;
}						t_dir;

typedef enum e_redir
{
	INFILE,
	HERE_DOC,
	OUTFILE_TRUNC,
	OUTFILE_APPEND
}						t_redir;

typedef struct s_file
{
	t_redir				redir_type;
	char				*limiter;
	char				*file_name;
	int					fd;
	struct s_file		*next;
}						t_file;

typedef enum e_node_type
{
	COMB = 1,
	PAR,
	PAR_OPEN,
	PAR_CLOSE,
	INF,
	CMD,
	REDIR,
	HD,
	OUTF_TRUNC,
	OUTF_APPEND,
	CMD_END,
	AND,
	OR,
	PIPE
}						t_node_type;

typedef t_node_type		t_tok_type;

typedef struct s_split
{
	t_tok_type			tok_type;
	t_tok_type			sub_tok_type;
	char				*str;
	struct s_split		*next;
}						t_split;

typedef t_split			t_expand;

typedef struct s_cmd
{
	t_file				*files;
	t_split				*copy;
	int					hd_rolls;
	char				**args;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_node
{
	t_node_type			node_type;
	t_cmd				*cmds;
	struct s_node		*left;
	struct s_node		*right;
	t_split				*first_token;
}						t_node;

#endif
