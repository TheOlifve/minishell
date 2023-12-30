# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 13:39:19 by rugrigor          #+#    #+#              #
#    Updated: 2023/12/06 19:39:00 by rugrigor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =libft.a

CC =cc

CFLAGS= -Wall -Wextra -Werror

SRCS =  ft_memset.c		\
		ft_bzero.c		\
		ft_memcpy.c		\
		ft_memmove.c 	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_strlen.c		\
		ft_isalpha.c 	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strcmp.c		\
		ft_strncmp.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_strnstr.c	\
		ft_striteri.c	\
		ft_atoi.c		\
		ft_calloc.c		\
		ft_strdup.c		\
		ft_substr.c		\
		ft_strjoin.c 	\
		ft_strtrim.c	\
		ft_split.c		\
		ft_itoa.c		\
		ft_atol.c		\
		ft_strmapi.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\
		ft_strcmp.c		\
		ft_strrcmp.c	\

SRCSB =	ft_lstnew.c			\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstclear.c		\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\

OBJS        = $(SRCS:.c=.o)
OBJSBONUS   = $(SRCSB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@ar r $(NAME) $(OBJS)

bonus: $(OBJSBONUS)
	@ar r $(NAME) $(OBJSBONUS)

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJSBONUS)

re: fclean all

.PHONY: all clean fclean re bonus
