# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/09/19 01:01:28 by rugrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BUILD = build

CC = cc

SRC = 	src/main.c				\
		src/cmds.c				\
		src/cd.c				\
		src/mems.c				\
		src/tokenizer.c			\
		src/simbol.c			\
		src/export.c			\
		src/get_next_line.c		\
		src/unset.c				\
		src/dollar.c			\
		src/parser_word.c		\
		src/parser_word2.c		\
		src/dollar2.c			\
		src/list_tree.c			\
		src/export2.c			\
		src/pars.c				\
		src/list_lcmd.c			\
		src/list_lexer.c		\
		src/wildcard.c			\
		src/engine.c			\
		src/pipex_b.c			\
		src/free.c				\
		src/utils.c				\
		src/redir.c				\
		src/utils2.c			\
		src/signal.c			\
		src/parser.c			\
		src/parser_operator.c		\
		src/pp_bb.c				\
		src/heredoc.c

LIBFT = libft

HEADER = ./includes/minishell.h

OBJ = $(patsubst %.c, %.o, $(SRC))

MINI = $(patsubst %.o, $(BUILD)/%.o, $(OBJ))

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=address

INC = -Ireadline/include -Ilibft

$(BUILD)/%.o: %.c $(HEADER) Makefile
	@mkdir -p $(BUILD)/src
	$(CC) $(inherited) -c $(CFLAGS) $(INC) $< -o $@

all: $(NAME)

$(NAME) : $(MINI)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(MINI) $(INC) -o $(NAME) -L./libft -lft -Lreadline/lib -lreadline 

config:
	mkdir -p readline
	./readline.sh readline

fclean: clean
	rm -rf $(NAME) $(BUILD)
	
clean:
	$(MAKE) clean -C $(LIBFT)
	rm -rf $(OBJ)


re: fclean all

.PHONY: all clean fclean re minishell config
