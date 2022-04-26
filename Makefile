# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faguilar <faguilar@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 10:32:04 by faguilar          #+#    #+#              #
#    Updated: 2022/04/26 11:08:22 by faguilar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus

CC = gcc
# FLAGS = -Wall -Wextra -Werror -g

LIFLAGS = -Llibft -l:libft.a
INCLUDE = -Iinclude

LIBS = include/pipex.h libft/libft.a
SRCS_PATH = ./srcs
SRCS = $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/terminate.c \
		$(SRCS_PATH)/utils.c
OBJS = ${SRCS:.c=.o}
INCLUDE = -Iinclude

LIBS_B = bonus/include/pipex_bonus.h libft/libft.a
SRCS_PATH_B = ./bonus/srcs
SRCS_B = $(SRCS_PATH_B)/main_bonus.c \
				$(SRCS_PATH_B)/terminate_bonus.c \
				$(SRCS_PATH_B)/utils_bonus.c
OBJS_B = ${SRCS_B:.c=.o}
INCLUDE_B = -Ibonus/include

# .c.o:	%.o : %.C
# 	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(LIBS) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIFLAGS) -o $(NAME)

$(LIBS):
	make -C libft

clean:
	make -C libft/ clean
	@rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	make -C libft/ fclean
	@rm $(NAME)

re: fclean all

re_bonus: fclean bonus

bonus: $(NAME_B)

$(NAME_B): $(OBJS_B) $(LIBS)
	$(CC) $(FLAGS) $(OBJS_B) $(LIFLAGS) -o $(NAME_B)

.PHONY: all clean fclean re