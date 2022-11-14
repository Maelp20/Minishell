

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 15:45:58 by mpignet           #+#    #+#              #
#    Updated: 2022/11/14 15:30:55 by mpignet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS	= \
			exec.c\
			builtin_cd.c\
			builtin_echo.c\
			builtin_pwd.c\
			builtin_env.c\
			builtin_exit.c\
			ft_exec_utils.c\
			get_env.c get_path.c detect_quote.c init.c main.c\

SRCDIR		= srcs/
OBJDIR 		= objs
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
MFLAG		= -lreadline
NAME	= minishell
RM		= rm -fd

all:		${NAME}

${OBJDIR}/%.o : ${SRCDIR}%.c ${INC}
				mkdir -p ${OBJDIR}
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