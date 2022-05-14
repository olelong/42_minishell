# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afaure <afaure@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/21 19:14:23 by olelong           #+#    #+#              #
#    Updated: 2022/01/25 01:41:30 by afaure           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

INCLUDEFILES =	include/defs.h \
				include/minishell.h \
				include/structs.h \
				libft/libft.h

SRCS_BUILTINS =	srcs/builtins/echo.c \
				srcs/builtins/env.c \
				srcs/builtins/exit.c \
				srcs/builtins/export.c \
				srcs/builtins/ft_cd.c \
				srcs/builtins/pwd.c \
				srcs/builtins/unset.c

SRCS_ENV = 		srcs/environment/environment.c \
				srcs/environment/environment_utils.c

SRCS_EXEC = 	srcs/exec/exec_command_utils.c \
				srcs/exec/exec_command.c \
				srcs/exec/exec_command2.c \
				srcs/exec/search_utils.c \
				srcs/exec/search.c \
				srcs/exec/exec_line.c \
				srcs/exec/exec_tree.c \
				srcs/exec/exec_utils0.c \
				srcs/exec/exec_utils1.c

SRCS_EXPAND =	srcs/expansion/add_redirs.c \
				srcs/expansion/expand_cmd.c \
				srcs/expansion/expand_parameter.c \
				srcs/expansion/expand_wrd.c \
				srcs/expansion/expansions_utils.c

SRCS_PARSE =	srcs/parsing/check_op.c \
				srcs/parsing/create_cmd.c \
				srcs/parsing/empty_line.c \
				srcs/parsing/init_copy.c \
				srcs/parsing/parse.c \
				srcs/parsing/parsing_heredoc.c \
				srcs/parsing/syntax_error.c \
				srcs/parsing/check_line.c \
				srcs/parsing/main_parse.c\
				srcs/parsing/parse_utils.c

SRCS_REDIR =	srcs/redir/do_redir.c \
				srcs/redir/heredocs.c \
				srcs/redir/undo_redirs.c \
				srcs/redir/heredoc_utils.c \
				srcs/redir/heredoc_utils2.c

SRCS_SIGNAL =	srcs/signals/signal_handlers.c \
				srcs/signals/signals_utils.c

SRCS_UTILS  =	srcs/utils/cmd_list_utils.c \
				srcs/utils/print_utils.c \
				srcs/utils/wrd_list_utils.c \
				srcs/utils/utils.c

SRCS_ERR = 		srcs/error_quit/errors.c \
				srcs/error_quit/free_all.c \
				srcs/error_quit/quit.c

OBJ =	$(SRCS_BUILTINS:.c=.o) $(SRCS_ENV:.c=.o) $(SRCS_EXEC:.c=.o) $(SRCS_EXPAND:.c=.o) $(SRCS_PARSE:.c=.o) $(SRCS_SIGNAL:.c=.o) $(SRCS_UTILS:.c=.o) $(SRCS_ERR:.c=.o) $(SRCS_REDIR:.c=.o) 

INCLUDES	=	 -I include -I libft
CFLAGS		=	-Wall -Werror -Wextra $(INCLUDES)
LIBFT		= 	libft/libft.a


all: $(NAME)

%.o: %.c $(INCLUDEFILES)
	cc $(CFLAGS) -c $< -o $(<:.c=.o)

$(LIBFT): libft
	$(MAKE) -C libft --no-print-directory

$(NAME): $(OBJ) $(INCLUDEFILES) $(LIBFT)
	cc $(CFLAGS) $(OBJ) -o $(NAME) -L libft -lft -l readline

clean :
	$(MAKE) clean -C libft --no-print-directory
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft --no-print-directory
	rm -rf $(NAME)

re: 	fclean all

.phony: all clean fclean re
