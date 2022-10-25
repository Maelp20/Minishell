# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpignet <mpignet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 15:45:58 by mpignet           #+#    #+#              #
#    Updated: 2022/10/25 16:26:07 by mpignet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS	= \
			main.c\
			ft_cd.c\
			ft_echo.c\
			ft_pwd.c\
			ft_env.c\

SRCDIR		= srcs/
OBJDIR 		= objs
OBJS		= ${addprefix ${OBJDIR}/, ${SRCS:.c=.o}}
INC			= inc/main.h

# /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
LIBFT_DIR = ./libft
LIBFT = ${LIBFT_DIR}/libft.a


# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */

CC		= gcc
CFLAGS	= -g -Wall -Wextra
LFLAGS	= -L ${LIBFT_DIR} -lft
NAME	= minishell
RM		= rm -fd

all:		${NAME}

${OBJDIR}/%.o : ${SRCDIR}%.c ${INC}
				mkdir -p ${OBJDIR}
				${CC} ${CFLAGS} -c $< -o $@

${LIBFT} :	
			make -C ${LIBFT_DIR} --no-print-directory

${NAME}:	${OBJS}	${LIBFT}
			${CC} ${CFLAGS} ${OBJS} ${LFLAGS} -o ${NAME}

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