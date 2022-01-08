NAME = pipex
CC = gcc
# FLAGS = -Wall -Wextra -Werror

LIB_FLAGS = -Llibft -lft -g
INCLUDE = -Iinclude
LIBS = include/*.h libft/libft.a

SRCS_PATH = ./srcs
SRCS = $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/farewell.c \

all: $(NAME)

$(NAME): $(SRCS) $(LIBS)
	$(CC) $(FLAGS) -o $(NAME) $(SRCS) $(LIB_FLAGS) $(INCLUDE)

$(LIBS):
	make -C libft

clean:
	make -C libft/ clean
	rm -rf $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re