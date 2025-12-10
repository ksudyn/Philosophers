# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/09 12:49:14 by ksudyn            #+#    #+#              #
#    Updated: 2025/12/10 20:15:15 by ksudyn           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -O0
INCLUDES = -I ./includes

SRCS = src/ft_error.c\
		src/init_bonus.c\
		src/main.c \
		src/philo_routine_utils.c \
		src/philo_routine.c\
		src/process_manager.c\
		src/spawn_philosophers.c\
		src/utils_bonus_2.c\
		src/utils_bonus.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
