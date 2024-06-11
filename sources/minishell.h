/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:51:40 by cdutel            #+#    #+#             */
/*   Updated: 2024/06/04 20:54:06 by dwayenbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "minishell_ascii.h"
# include "minishell_errors.h"
# include "minishell_structs.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# define MAX_SIZE 4096
# ifndef DEBUG_TTY
#  define DEBUG_TTY 0
# endif
# ifndef DEBUG_RL
#  define DEBUG_RL 0
# endif
# ifndef INTRO
#  define INTRO 1
# endif
# define LLMAX 9223372036854775807
# define LLMIN 9223372036854775808ULL

/****************************/
/*********Builtins***********/
/****************************/

/*Builtins*/
int			cd_bltin(char **dir, t_mini *mini, int is_child);
int			echo_bltin(char **arg, t_mini *mini, int is_child);
int			env_bltin(char **envp, t_mini *mini, int is_child);
int			exit_bltin(t_mini *mini, char **args, int is_child);
int			export_bltin(char **to_add, t_mini *mini, int is_child);
int			sort_and_print_env(char **env, t_mini *mini, int is_child);
int			pwd_bltin(t_mini *mini, char **args, int is_child);
int			get_curr_dir_name(char **pathname, int err_msg);
int			unset_bltin(char **to_unset, t_mini *mini, int is_child);

/*Cd_utils*/
int			change_env(char **env, char *pwd, char *oldpwd, t_mini *mini);
void		cd_err(t_mini *mini, int errnum);
void		cd_err_2(t_mini *mini);
void		cd_err_3(t_mini *mini, char *dir);
void		free_cd(char **pwd, char **oldpwd);

/*Export_utils*/
int			contains_equal(char *env_line);
int			get_size(char *to_add, char *env_line);
int			check_to_add(t_mini *mini, char *to_add, int *trigger);
int			export_error(t_mini *mini, int c, char *s);

/*Unset_utils*/
int			env_len(char **env);
void		unset_malloc_err(t_mini *mini);

/****************************/
/*********EXEC************/
/****************************/

/*Arnaque*/
int			err_printf(char *input_printf, char *str2, char *str3, char *str4);
int			err_printf_plus(char *input_printf, char **strs, int size);
int			err_printf_fd_hd(char *printf_prompt, char **strs, int line_count);
int			err_printf_quote(char *printf_prompt, char c);
/*Clean_all*/
int			free_on_failure(t_mini *mini);
int			free_at_the_end(t_mini *mini);

/*Exec_builtins*/
int			is_builtin(char **arg);
int			exec_builtin_child(char **arg, t_mini *mini, int *pipe_fd,
				t_cmd *cur_cmd);
int			exec_builtin_parent(t_cmd *cur_cmd, t_mini *mini,
				char ***full_file);

/*Exec_cmd*/
int			execute(t_cmd *cur_cmd, t_mini *mini, int *pipe_fd);
int			subshell_magik(t_cmd *cur_cmd, t_mini *mini);

/*Exec_loop*/
int			exec_loop(t_node *cur, t_mini *mini, char **full_file);
void		remove_from_hd_list(int fd, t_heredocs **heredocs, int to_close);

/*Exec_node*/
int			exec_node(t_node *cur, t_mini *mini);

/*Exec_node_utils*/
void		reset_fds(t_mini *mini);
int			set_path_tab(t_mini *mini);
void		close_hd(t_cmd *cmd, t_heredocs **heredocs);

/*File_opening*/
int			open_files(t_cmd *cur_cmd, t_mini *mini, char **full_files,
				int *process_pipe);
int			printf_syntax_err(t_mini *mini, char *filename);

/*Manage_errors*/
void		print_file_error(t_file *cur_file, t_mini *mini);

/*Select_node*/
int			select_node(t_node *current, t_mini *mini);
/*Subshell.c*/
int			subshell_magik(t_cmd *cur_cmd, t_mini *mini);
/*Utils*/
void		ft_le_xav(char **dest);
char		*get_env_variable(char **env, char *variable);
char		*get_env_variable_2(char **env, char *variable, t_mini *mini);
int			init_mini_struct(t_mini *mini, char **envp);

/*Utils2*/
int			get_envp(char **envp, char ***mini_env);
int			is_dir(char *path);
void		destroy_tab(char ***output);
int			set_hiden_env(t_mini *mini);
int			ft_is_quote(char c);
/****************************/
/*********PARSING************/
/****************************/

/*ast_utils.c*/
t_node		*create_new_node(t_split *first_elem, t_node_type type);
int			create_tree(t_node **tree_top, t_split **elem);
void		remove_from_list(t_split **first, t_split *to_remove);
int			is_only_par(t_split *elem);
t_node_type	get_node_type(t_split *elem);
/*ast.c*/
void		remove_parenthesis(t_node *node);
int			split_comb_node(t_node *current);
int			decomp_node(t_node *current);
t_split		*get_last_tok(t_split **first);
int			destroy_tree(t_node **tree_top, int value);
/*cmds_parsing_utils.c*/
void		addback_file_list(t_file **files, t_file *new_file);
int			get_arg_count(t_split *start, int length);
void		init_file_output(t_file *output, char *str, t_tok_type redir_type,
				t_heredocs **heredocs);
int			destroy_cmds_list(t_cmd **first_cmds, int value);
void		destroy_file_list(t_file **first);
t_split		*copy_split_elem(t_split *current);
/*cmds_parsing.c*/
void		process_in_par(t_tok_type type, int *in_par);
int			copy_list(t_split **copy, t_split *origin);
int			alloc_output_args(char ***output, t_split *first, int length);
t_cmd		*parse_cmds(t_split *first_token, t_heredocs **heredocs, int i,
				int in_par);
int			addback_cmds_list(t_cmd **start, t_split *first_token, int length,
				t_heredocs **heredocs);
t_cmd		*create_new_cmd(t_split *first, int length, t_heredocs **heredocs);
int			set_cmd_arg(t_cmd *output, t_split *first, int length,
				t_heredocs **heredocs);
int			add_file_list(t_file **files, t_split *current,
				t_heredocs **heredocs, int *length);
int			update_heredocs(t_split *current, int length, t_cmd *output,
				t_heredocs **heredocs);
/*debug.c*/
void		print_list(t_split *first);
void		print_args(char **args);
void		print_files(t_file *files);
void		print_commands(t_cmd *first);
void		print_tree(t_node *tree_top, t_mini *mini, char **files,
				t_heredocs **heredocs);

/*get_curr_dir_files.c*/
int			get_files(char ***dir_content);
int			process_dir_list(t_dir **first, char ***output);
void		destroy_dir_list(t_dir **first);
int			addback_dir_list(t_dir **first, char *str);
/*line_first_read.c*/
int			line_parser(char *line, t_split **line_list);
int			add_arg_to_list(char *line, int *i, t_split **first_elem);
t_split		*create_new_split_elem(char *line, int *i);
int			get_char_count(char *line, int *i);

/*other_utils.c*/
int			ft_isspace(char c);
/*parser_utils.c*/
int			destroy_split_list(t_split **first, int return_val);
void		destroy_split(t_split *split);
/*parser.c*/
void		quote_trimmer(char *str);
int			has_quote(char *str);
int			quote_validity(char *str, int *exit_status);
/*signals.c*/
void		signal_heredoc(int sig);
int			signal_default(void);
void		rl_sigint(int sig);
int			signal_ms(void);
/*syntax_errors.c*/
int			syntax_err_msg(int err_value, char *current_token, char *next_token,
				int open_hd);
int			syntax_err_msg_par_open(int err_value, char *current_token,
				char *token, int open_hd);
/*tokenizer.c*/
void		add_token_types(t_split **first_elem);
t_tok_type	get_tok_type(char *str);
t_tok_type	get_sub_tok_type(t_tok_type type);
/*tokens_utils.c*/
t_node_type	is_redir_token(char *str);
t_node_type	is_cmd_end_token(char *str);
t_node_type	is_par(char *str);
t_node_type	is_word(char *str);
int			is_token(char *str);
/*trimming.c*/
int			trimming_process(t_split **first);
int			need_trim(char *str);

/****************************/
/*********WILDCARDS**********/
/****************************/

/*wildcards.c*/
int			expand_one_wildcard(t_split **tok_with_w, char **files);
int			w_process_all(char **trim, char **files, t_split **wildcard_list,
				t_split **tok_with_w);
int			w_get_back_offset(char **result, char *wild);
int			w_get_front_offset(char **result, char *wild);
/*wildcards_dir.c*/
int			is_wildcard_dir(char *wild);
/*wildcards_match.c*/
int			wildcard_match(char *wildcard, char *str);
int			w_wildcard_match_start(char *wildcard, char *str, int *comp1);
int			wildcard_loop(char *wildcard, char *str, int *i, int *j);
int			w_wildcard_match_end(char *wildcard, char *str, int i, int j);
/*wildcards_redir.c*/
int			expand_one_wildcard_redir(char **str_with_w, char **files);
int			check_redir_ambiguity(t_split *wildcard, t_split **tok_with_w);
int			expand_token_list(t_split **first, char **file_list);

/*wildcards_utils.c*/
t_split		*create_list_elem(char *str);
int			has_wildcard(char *str);
void		w_free_trim(char **trim);
int			add_back_wildcard_list(t_split **first, char *str);
char		*get_wildcard_result(char *front_offset, char *file,
				char *back_offset);

/****************************/
/*********HEREDOCS***********/
/****************************/

/*heredoc_expand.c*/
int			heredoc_expander(int *heredoc_fd, t_mini *mini, int *process_pipe);
int			expand_in_child(int heredoc_fd, int write_pipe, t_mini *mini);
int			hd_exp_parent(int *heredoc_fd, int pid, int *pipe_fd);
int			get_heredoc_content_gnl(int fd, char *limiter, t_mini *mini);
/*heredoc_expand_utils.c*/
int			close_all_in_child(t_mini *mini, int *pipe_fd, int heredoc_fd,
				int value);
void		prompt_gnl(int istty, char *line, int fd);
int			process_final_line(char *line, t_mini *mini, char *limiter);
void		trim_dollar(char *str);
void		dollar_trimmer(char *str);
/*heredoc_realine.c*/
int			get_heredoc_content_rl(int write_fd, int read_fd, char *limiter,
				t_mini *mini);
int			get_heredoc_content_rl_child(int fd, char *limiter, t_mini *mini);
/*heredoc_utils.c*/
int			generate_random(char *output, int size);
int			get_hd_name(char *hd_name);
int			get_first_heredoc(t_heredocs **heredocs);
int			addback_hd_list(t_heredocs **heredocs, int fd);
void		remove_hd_list(t_heredocs **first);
/*heredoc_writing.c*/
int			write_expanded_line(int fd, char *line, t_mini *mini,
				char need_exp);
int			write_env_var(char *dolls, int *i, int fd, t_mini *mini);
int			print_var(char *dolls, int *i, char **env, int fd);
/*open_heredocs.c*/
int			get_hd_file(char *limiter, t_mini *mini);
/****************************/
/*********EXPAND*************/
/****************************/

/*args_utils.c*/
void		remove_empty_args(t_cmd *first_cmd);
void		trim_args(t_cmd *cmds);
int			char_gets_dolls_written_quote(char c);
/*dollar_expand_list_utils.c*/
char		*process_list(t_expand **first);
int			add_to_expand_dollar_list(t_expand **first, char *str, int *i,
				t_mini *mini);
int			add_to_expand_list(t_expand **first, char *str, int i);
/*dollard_expand_quote.c*/
int			do_both_expand_quote(t_expand **first, char *str, int *i,
				t_mini *mini);
t_expand	*create_expand_dollar_quote(char *str, int *i, t_mini *mini);
int			add_to_expand_dollar_list_quote(t_expand **first, char *str, int *i,
				t_mini *mini);
/*dollar_expand_utils.c*/
int			has_dollar(char *str);
t_expand	*create_new_expand(char *str, int i);
void		get_str_output(char **str, int *i, int type);
void		get_str_output_env(char *entry, char **str, int *i, char **envp);
int			is_valid_env_char(char c);
/*dollar_expand.c*/
int			dollar_expander(t_split **line_list, t_mini *mini, int in_par);
void		get_quote_status(char c, char *is_quote);
char		*expand(char *str, t_mini *mini, t_expand **first);
t_expand	*create_expand_dollar(char *str, int *i, t_mini *mini);
/*node_expander.c*/
void		check_args(char **args);
int			expand_node(t_node *node, t_mini *mini, char **wildcard_files,
				t_heredocs **heredocs);
int			expand_file(t_file *file, t_mini *mini, char **files);
int			expand_file_dollar(char **file_name, t_mini *mini,
				t_expand **first);

/****************************/
/*********LINE_VALIDITY******/
/****************************/

/*line_is_walid.c*/
int			line_is_walid(t_split **first, int *open_par, t_mini *mini,
				int open_hd);
int			line_is_walid_pipe(t_split **first, int *open_par, t_mini *mini,
				int open_hd);
int			check_first_token(t_split *first, int *exit_status, int open_hd);
int			get_syntax_err_value(t_split *current);
char		line_is_walid_quotes(char *line);
/*line_is_walid2.c*/
int			line_is_walid_redir(t_split **first, int *open_par, t_mini *mini,
				int open_hd);
int			line_is_walid_cmd_end(t_split **first, int *open_par, t_mini *mini,
				int open_hd);
int			line_is_walid_par_open(t_split **first, int *open_par, t_mini *mini,
				int open_hd);
int			line_is_walid_par_close(t_split **first, int *open_par,
				t_mini *mini, int open_hd);
int			line_is_walid_cmd(t_split **first, int *open_par, t_mini *mini,
				int open_hd);
/*process_line.c*/
int			process_line(char *line, t_mini *mini);
int			check_after_subshell_syntax(t_split *first, int open_hd);
/****************************/
/*********READLINE***********/
/****************************/

/*gnl_loop.c*/
int			gnl_loop(t_mini *mini);
/*readline_utils.c*/
int			only_space(char *line);
void		remove_nl(char *line);
/*readline.c*/
int			process_empty_line(t_mini *mini);
void		loop_beginning_rl(char **line, char **prompt, t_mini *mini);
int			readline_loop(t_mini *mini, char *prompt);

/****************************/
/*********CLEANING***********/
/****************************/

/*free_everything.c*/
int			destroy_mini(t_mini *mini, int value);
void		close_fds(t_mini *mini);
void		kill_processes(t_proc **processes);
int			free_everything(t_mini *mini, int value);
/*processes.c*/
int			add_proc_list(t_proc **processes, int pid);
void		remove_proc_from_list(t_proc **processes, int pid);
void		destroy_proc_list(t_proc **processes);
#endif
