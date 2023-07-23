# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reira <reira@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 17:05:16 by rtakashi          #+#    #+#              #
#    Updated: 2023/07/23 00:33:02 by reira            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a
GNL = ../gnl/get_next_line.c ../gnl/get_next_line_utils.c
SRCS = command.c export.c pwd.c echo.c export_nooption.c heredoc.c redirection.c \
	env.c append.c error.c get_env_list.c main.c unset.c cd.c exit.c get_word_list.c \
	minishell_utils.c free.c input_output_operation.c $(GNL)
OBJS = ${addprefix $(OBJS_DIR)/,$(SRCS:.c=.o)}
OBJS_DIR = objs

RM = rm -f

.DEFAULT_GOAL :=$(NAME)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
${OBJS_DIR}/%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	make clean -C libft
	$(RM) $(OBJS) $(LIBFT) $(GNL)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(GNL)

re: fclean all

.PHONY: all clean fclean re leaks
