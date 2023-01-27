# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 15:45:58 by mpignet           #+#    #+#              #
#    Updated: 2023/01/27 20:03:59 by yanthoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS	= \
			exec/exec.c\
			exec/exec_open_files.c\
			exec/exec_handle_fds.c\
			exec/exec_utils.c\
			exec/exec_utils_envp.c\
			exec/exec_get_cmd_path.c\
			exec/exec_error_management.c\
			exec/print_errors.c\
			exec/builtin_cd.c\
			exec/builtin_echo.c\
			exec/builtin_pwd.c\
			exec/builtin_env.c\
			exec/builtin_exit.c\
			exec/builtin_unset.c\
			exec/builtin_export.c\
			exec/builtin_export_display.c\
			parsing/[1]main.c				parsing/[2]get_env.c\
			parsing/[3]split_space.c		parsing/[4]split_space_utils.c\
			parsing/[5]split_separator.c	parsing/[6]split_separator_utils.c\
			parsing/[7]expand.c 			parsing/[8]expand_utils.c	parsing/[8]expand_utils2.c\
			parsing/[9]clean_quotes.c\
			parsing/[10]check_tok_err.c\
			parsing/[11]process_redir.c 	parsing/[12]redir_type.c\
			parsing/[13]fill_nodes.c 		parsing/[14]fill_nodes_utils.c\
			parsing/clean.c 				parsing/init.c\
			
SRCDIR		= srcs/
OBJDIR 		= objs
SUBOBJ		= objs/exec objs/parsing
OBJS		= ${addprefix ${OBJDIR}/, ${SRCS:.c=.o}}
INC			= inc/exec.h
CINC		= -I ./inc/

# /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
LIBFT_DIR = ./libft
LIBFT = ${LIBFT_DIR}/libft.a


# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */

CC		= cc
CFLAGS	= -g -Wall -Wextra -Werror -MMD
LFLAGS	= -L ${LIBFT_DIR} -lft
MFLAG	= -lreadline
NAME	= minishell
RM		= rm -rfd

all:		${NAME}

# $(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 				mkdir -p ${OBJDIR} ${SUBOBJ}
# 				${CC} ${CFLAGS} ${CINC} -c $< -o $@

${OBJDIR}/%.o : ${SRCDIR}%.c ${INC}
				mkdir -p ${OBJDIR} ${SUBOBJ}
				${CC} ${CFLAGS} ${CINC} -c $< -o $@

${LIBFT} :	
			make -C ${LIBFT_DIR} --no-print-directory

${NAME}:	${OBJS}	${LIBFT}
			${CC} ${CFLAGS} ${OBJS} ${MFLAG} ${LFLAGS} -o ${NAME}

clean:
			${RM} ${OBJS} ${OBJDIR}
			make clean -C ${LIBFT_DIR} --no-print-directory

fclean:		
			${RM} ${OBJS} ${OBJDIR}
			${RM} ${NAME}
			make fclean -C ${LIBFT_DIR} --no-print-directory

re:			fclean
			make all

.PHONY: 	all clean fclean re
-include ./exec/*.d
-include ./parsing/*.d

##.SILENT:
