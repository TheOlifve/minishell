# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrahovha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/11/17 20:06:04 by hrahovha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BUILD = build

CC = cc

SRC =	src/cd.c				\
		src/main.c				\
		src/cmds.c				\
		src/mems.c				\
		src/free.c				\
		src/bonus.c				\
		src/pp_bb.c				\
		src/unset.c				\
		src/redir.c				\
		src/utils.c				\
		src/simbol.c			\
		src/export.c			\
		src/dollar.c			\
		src/engine.c			\
		src/utils2.c			\
		src/signal.c			\
		src/parser.c			\
		src/pipex_b.c			\
		src/heredoc.c			\
		src/dollar2.c			\
		src/export2.c			\
		src/pipex_b2.c			\
		src/wildcard.c			\
		src/list_tree.c			\
		src/tokenizer.c			\
		src/list_lexer.c		\
		src/tokenizer2.c		\
		src/parser_word.c		\
		src/parser_word2.c		\
		src/get_next_line.c		\
		src/parser_operator.c

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
