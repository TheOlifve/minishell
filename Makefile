# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 10:59:36 by rugrigor          #+#    #+#              #
#    Updated: 2023/12/20 14:44:37 by rugrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

BUILD = build

CC = cc

SRC = 	src/main.c				\
		src/cd.c				\
		src/dup.c				\
		src/cmds.c				\
		src/free.c				\
		src/mems.c				\
		src/free2.c				\
		src/unset.c				\
		src/utils.c				\
		src/bonus.c				\
		src/pp_bb.c				\
		src/redir.c				\
		src/simbol.c			\
		src/export.c			\
		src/engine.c			\
		src/dollar.c			\
		src/bonus2.c			\
		src/utils2.c			\
		src/utils3.c			\
		src/utils4.c			\
		src/signal.c			\
		src/parser.c			\
		src/heredoc.c			\
		src/pipex_b.c			\
		src/export2.c			\
		src/export3.c			\
		src/dollar2.c			\
		src/engine2.c			\
		src/wildcard.c			\
		src/pipex_b2.c			\
		src/tokenizer.c			\
		src/list_tree.c			\
		src/tokenizer2.c		\
		src/list_lexer.c		\
		src/parser_word.c		\
		src/parser_word2.c		\
		src/get_next_line.c		\
		src/parser_operator.c

LIBFT = libft

HEADER = ./includes/minishell.h

OBJ = $(patsubst %.c, %.o, $(SRC))

MINI = $(patsubst %.o, $(BUILD)/%.o, $(OBJ))

CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address

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
	rm -rf $(OBJ) $(BUILD)

re: fclean all

.PHONY: all clean fclean re minishell config
