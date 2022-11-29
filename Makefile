# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 15:45:58 by mpignet           #+#    #+#              #
#    Updated: 2022/11/29 16:20:13 by yanthoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS	= \
			exec/exec.c\
			exec/exec_open_files.c\
			exec/exec_utils.c\
			exec/exec_error_management.c\
			exec/builtin_cd.c\
			exec/builtin_echo.c\
			exec/builtin_pwd.c\
			exec/builtin_env.c\
			exec/builtin_exit.c\
			exec/builtin_unset.c\
			exec/builtin_export.c\
			parsing/get_env.c\
			parsing/detect_quote.c\
			parsing/init.c main.c\

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

CC		= gcc
CFLAGS	= -g -Wall -Wextra
LFLAGS	= -L ${LIBFT_DIR} -lft
MFLAG	= -lreadline
NAME	= minishell
RM		= rm -rfd

all:		${NAME}

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

.SILENT: