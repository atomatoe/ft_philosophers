# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atomatoe <atomatoe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 01:14:34 by atomatoe          #+#    #+#              #
#    Updated: 2020/11/24 01:15:23 by atomatoe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_three

INCLUDE = philo_three.h

SRCS = ft_philo_life.c ft_philosoph.c main.c utils1.c utils2.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
		@clang  $(CFLAGS) $(SRCS) -o $(NAME)

%.o: %.c $(INCLUDE)
		@clang $(CFLAGS) -c $< -o $@

clean:
		@rm -rf $(OBJS)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re