# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwayenbo <dwayenbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/18 08:19:01 by dwayenbo          #+#    #+#              #
#    Updated: 2024/06/04 19:08:22 by dwayenbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################
#							COLORS							   #
################################################################
# Bold High Intensity
BIBlack=\033[1;90m
BIRed=\033[1;91m
BIGreen=\033[1;92m
BIYellow=\033[1;93m
BIBlue=\033[1;94m
BIPurple=\033[1;95m
BICyan=\033[1;96m
BIWhite=\033[1;97m
# Bold
BBlack=\033[1;30m
BRed=\033[1;31m
BGreen=\033[1;32m
BYellow=\033[1;33m
BBlue=\033[1;34m
BPurple=\033[1;35m
BCyan=\033[1;36m
BWhite=\033[1;37m
# Regular Colors
Black=\033[0;30m
Red=\033[0;31m
Green=\033[0;32m
Yellow=\033[0;33m
Blue=\033[0;34m
Purple=\033[0;35m
Cyan=\033[0;36m
White=\033[0;37m

COLORS=$(BIRed) $(BIGreen) $(BIYellow) $(BIBlue) $(BIPurple) $(BICyan)
COMPTEUR = 0
OFFSET = 0
################################################################
#							LIBS							   #
################################################################

GNL_DIR = gnl/
GNL =	gnl gnl_utils

LIBFT_AND_CO = 	$(addprefix $(GNL_DIR), $(GNL))\
				ft_bzero  ft_isalnum ft_isalpha ft_isdigit  ft_itoa\
				ft_putnbr_fd ft_split ft_strchr	ft_strcmp ft_strcpy\
				ft_strdup ft_strjoin_with_c ft_strjoin ft_strlcpy ft_strlen_to_c\
				ft_strlen ft_strncmp ft_strnstr ft_strdup2
				 
				
################################################################
#							PROJ							   #
################################################################

NAME =			minishell
NAME_BONUS =	minishell_bonus

BUILTIN = 		cd_bltin echo_bltin env_bltin export_bltin export_sort_bltin\
				export_utils pwd_bltin unset_bltin unset_utils exit_bltin\
				cd_bltin_utils cd_change_env

CLEANING =		free_everything processes

EXEC = 			clean_all exec_builtins exec_cmd exec_node exec_node_utils\
				file_opening manage_error select_node utils utils2 arnaque\
				exec_loop set_env subshell file_opening_utils

EXPAND =		args_utils dollar_expand_list_utils dollar_expand_utils dollar_expand\
				dollar_expand_quote node_expander

HEREDOCS =		heredoc_expand heredoc_utils heredoc_writing open_heredocs\
				heredoc_expand_utils heredoc_readline

LINE_VALIDITY =	line_is_walid line_is_walid2 process_line

PARSER = 		ast_utils ast cmds_parsing_utils cmds_parsing_utils2 cmds_parsing\
				debug get_curr_dir_files line_first_read \
				parser_utils parser set_cmd_arg signals syntax_errors tokenizer\
				tokens_utils trimming 

READLINE = 		gnl_loop readline_utils readline

WILDCARDS =		wildcards_dir wildcards_match wildcards_redir wildcards_utils wildcards\
				expand_wildcards


LIBFT_AND_CO_DIR = libft/
LIBFT_AND_CO_SRC = $(addprefix $(LIBFT_AND_CO_DIR), $(LIBFT_AND_CO))
BUILTIN_DIR = builtin/
BUILTIN_SRC = $(addprefix $(BUILTIN_DIR), $(BUILTIN))
CLEANING_DIR = cleaning/
CLEANING_SRC = $(addprefix $(CLEANING_DIR), $(CLEANING))
EXEC_DIR = exec/
EXEC_SRC = $(addprefix $(EXEC_DIR), $(EXEC))
EXPAND_DIR = expand/
EXPAND_SRC = $(addprefix $(EXPAND_DIR), $(EXPAND))
HD_DIR = heredocs/
HD_SRC = $(addprefix $(HD_DIR), $(HEREDOCS))
LINE_VALIDITY_DIR = line_validity/
LINE_VALIDITY_SRC = $(addprefix $(LINE_VALIDITY_DIR), $(LINE_VALIDITY))
PARSER_DIR = parser/
PARSER_SRC = $(addprefix $(PARSER_DIR), $(PARSER))
READLINE_DIR = readline/
READLINE_SRC = $(addprefix $(READLINE_DIR), $(READLINE))
WILD_DIR = wildcards/
WILD_SRC = $(addprefix $(WILD_DIR), $(WILDCARDS))
SRCS = minishell $(LIBFT_AND_CO_SRC) $(BUILTIN_SRC) $(CLEANING_SRC) $(EXEC_SRC) $(EXPAND_SRC)\
			$(HD_SRC) $(LINE_VALIDITY_SRC) $(PARSER_SRC) $(READLINE_SRC) $(WILD_SRC) 
SRCS_DIR = sources/

OBJS_DIR = objs_and_deps/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS)))

ALL_DIRS = $(addprefix $(OBJS_DIR),\
									$(BUILTIN_DIR)\
									$(CLEANING_DIR)\
									$(EXEC_DIR)\
									$(EXPAND_DIR)\
									$(HD_DIR)\
									$(LINE_VALIDITY_DIR)\
									$(PARSER_DIR)\
									$(READLINE_DIR)\
									$(WILD_DIR)\
									$(addprefix $(LIBFT_AND_CO_DIR),\
																	 $(GNL_DIR)))

DEPENDENCIES = 	$(patsubst %.o,%.d, $(OBJS))
intro=1
HEADERS =
VG_FLAG =
ifeq ($(intro), 0)
INTRO_FLAG = -D INTRO=0 
endif
CFLAGS = -Wall -Werror -Wextra $(VG_FLAG)$(INTRO_FLAG)-MMD

################################################################
#							RULES							   #
################################################################

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	$(eval COMPTEUR=$(shell expr $(COMPTEUR) + $(OFFSET)))
	$(eval OFFSET=$(shell expr $(OFFSET) + 1))
	$(eval OFFSET=$(shell expr $(OFFSET) % 2))
	$(eval COMPTEUR=$(shell expr $(COMPTEUR) % 6))
	$(eval INDEX=$(shell expr $(COMPTEUR) + 1))
	@printf "$(word $(INDEX),$(COLORS))COMPILING OBJ : $@\n"
	@mkdir -p $(ALL_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(BIGreen)COMPILING BINARY : $(NAME)\n$(White)"
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	
$(NAME_BONUS): $(OBJS)
	@printf "$(BIGreen)COMPILING BONUS BINARY : $(NAME_BONUS)\n$(White)"
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME_BONUS)

re: fclean all

bonus: $(NAME_BONUS)

no_intro:
	$(MAKE) re intro=0
	
clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

.PHONY: all clean fclean bonus re 

-include $(DEPENDENCIES)
