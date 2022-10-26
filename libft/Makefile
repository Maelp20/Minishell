# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 17:15:24 by yanthoma          #+#    #+#              #
#    Updated: 2022/08/29 12:12:14 by yanthoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a

SRCS	=	ft_atoi.c	ft_isalpha.c	ft_itoa.c	ft_memmove.c\
			ft_putnbr_fd.c		ft_strdup.c\
			ft_tolower.c	ft_bzero.c	ft_isascii.c	ft_memchr.c\
			ft_memset.c	ft_putstr_fd.c	ft_striteri.c	ft_strlen.c\
			ft_strrchr.c 	ft_toupper.c	ft_calloc.c	ft_isdigit.c\
			ft_memcmp.c	ft_putchar_fd.c	ft_split.c	ft_strjoin.c\
			ft_strmapi.c	ft_strtrim.c	ft_isalnum.c	ft_isprint.c\
			ft_memcpy.c	ft_putendl_fd.c	ft_strlcat.c ft_strchr.c\
			ft_substr.c ft_strlcpy.c ft_strnstr.c ft_strncmp.c\
			ft_lstadd_front.c	ft_lstdelone.c	ft_lstlast.c	ft_lstnew.c\
			ft_lstadd_back.c	ft_lstclear.c	ft_lstiter.c	ft_lstmap.c	ft_lstsize.c\
			ft_print_idu.c	ft_print_s_c_p_per.c ft_print_xX.c ft_printf.c\
			get_next_line_utils.c get_next_line.c\

OBJS	= ${SRCS:.c=.o} 

CC	= gcc

CFLAGS = -Wall -Wextra -Werror

all:	$(NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:		
	rm -f ${OBJS} 

fclean:	clean
	rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re
