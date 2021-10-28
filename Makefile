# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 09:43:37 by jalvarad          #+#    #+#              #
#    Updated: 2021/09/19 15:32:36 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

CFLAGS	= -Wall -Werror -Wextra #-fsanitize=address

SRCS	= pipex.c \
			ft_split.c \
			utils.c \
			otherutils.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc

all: $(NAME)

$(NAME): $(OBJS) pipex.h
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -c $(SRCS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean