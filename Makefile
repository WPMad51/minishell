NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

############################Sources########################
SRCS_DIR = sources/
FILES = minishell.c utils.c \

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

BUILTIN_DIR = sources/builtins/
FILES_BUILTIN = env_bltin.c pwd_bltin.c echo_bltin.c \
				unset_bltin.c export_bltin.c cd_bltin.c \

SRCS_BUILTIN = $(addprefix $(BUILTIN_DIR), $(FILES_BUILTIN))

###########################Objects#########################
OBJS = ${SRCS:.c=.o}
OBJS_BUILTIN = ${SRCS_BUILTIN:.c=.o}
OBJS_ALL = ${OBJS} ${OBJS_BUILTIN}

##########################Libs#############################
LIBFT = ./libft/libft.a
FT_PRINTF = ./libft/ft_printf/libftprintf.a
GNL = ./libft/get_next_line/libgnl.a
GNL_NO_MALLOC = ./libft/gnl_no_malloc/libgnlnomalloc.a
ALL_LIB = ${LIBFT} ${FT_PRINTF} ${GNL} ${GNL_NO_MALLOC} -lreadline

##########################Rules############################

all: ${NAME}

${NAME}: ${OBJS} ${OBJS_BUILTIN}
		@${MAKE} -C ./libft
		${CC} ${CFLAGS} ${OBJS} ${OBJS_BUILTIN} ${ALL_LIB} -o ${NAME}

clean:
	@${MAKE} -C ./libft fclean
	rm -f ${OBJS_ALL}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
