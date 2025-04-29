# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksudyn <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 19:10:16 by ksudyn            #+#    #+#              #
#    Updated: 2025/02/19 19:12:15 by ksudyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC		=	gcc
HEADERS = -I ./includes
CFLAGS	=	-Wall -Werror -Wextra -O0

SRCS := $(addprefix src/, \
				forks.c \
				ft_error.c \
				libft.c \
				main.c \
				number_of_philosophers.c \
				parse.c \
				routine.c \
				think.c \
				time_to_die.c \
				time_to_eat.c \
				time_to_sleep.c \
				utils.c \
				)

OBJS	=	$(patsubst src/%.c, obj/%.o, $(SRCS))

OBJDIR = obj

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
