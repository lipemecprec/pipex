NAME = pipex
CC = gcc
# FLAGS = -Wall -Wextra -Werror

LIB_FLAGS = -Llibft -Lft_printf -lft -g
INCLUDE = -Iinclude
LIBS = include/*.h libft/libft.a ft_printf/ft_printf.a

SRCS_PATH = ./srcs
SRCS = $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/farewell.c \
		$(SRCS_PATH)/utils.c
OBJS = ${SRCS:%.c=%.o}

all: $(NAME)

$(NAME): $(SRCS) $(LIBS) $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(SRCS) $(LIB_FLAGS) $(INCLUDE)

$(LIBS):
	make -C libft
	make -C ft_printf

clean:
	make -C libft/ clean
	make -C ft_printf/ clean
	rm -rf $(OBJS)

fclean: clean
	make -C libft/ fclean
	make -C ft_printf/ fclean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re