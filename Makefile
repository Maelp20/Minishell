# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 19:41:43 by yanthoma          #+#    #+#              #
#    Updated: 2022/10/26 14:46:39 by yanthoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME		= minishell

# ################################## #
#               COMMAND              #
# ################################## #
CC			= cc
MKDIR		= mkdir -p
RM			= rm -rf


# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= srcs
C_FILES		=	main.c \

SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR		= objs
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		= -Wall -Wextra -Werror -g
MFLAG		= -lreadline

CINCLUDES	= -I ./includes	\
			  -I ./libft

LIBFT		= ./libft/libft.a


# ################################## #
#                RULES               #
# ################################## #

all:		$(NAME)

$(NAME):	$(O_DIR) $(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) $(MFLAG) $(OBJS) $(LIBFT) -o $@

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@

$(O_DIR):
			$(MKDIR) $(O_DIR)

# ################################## #
#             DEPENDECIES...         #
# ################################## #

$(LIBFT):
			@make -C ./libft

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			@$(RM) $(O_DIR)
			@make -C ./libft clean
fclean:		clean
			@$(RM) $(NAME)
			@make -C ./libft fclean

re:			fclean all

.PHONY: all check clean fclean re