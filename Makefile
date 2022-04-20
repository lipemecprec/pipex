NAME = pipex
CC = gcc
# FLAGS = -Wall -Wextra -Werror

LIB_FLAGS = -Llibft -Lft_printf -l:libft.a -l:ft_printf.a -g
INCLUDE = -Iinclude

LIBS = include/*.h libft/libft.a \
		ft_printf/ft_printf.a ft_printf/include/ft_printf.h
SRCS_PATH = ./srcs
SRCS = $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/terminate.c \
		$(SRCS_PATH)/utils.c
OBJS = ${SRCS:%.c=%.o}
INCLUDE = -Iinclude

BONUS_LIBS = bonus/include/*.h libft/libft.a \
		ft_printf/ft_printf.a ft_printf/include/ft_printf.h
BONUS_SRCS_PATH = ./bonus/srcs
BONUS_SRCS = $(BONUS_SRCS_PATH)/main_bonus.c \
				$(BONUS_SRCS_PATH)/terminate_bonus.c \
				$(BONUS_SRCS_PATH)/utils_bonus.c
BONUS_OBJS = ${BONUS_SRCS:%.c=%.o}
BONUS_INCLUDE = -Ibonus/include

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

bonus: $(BONUS_SRCS) $(BONUS_LIBS) $(BONUS_OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(BONUS_SRCS) $(LIB_FLAGS) $(BONUS_INCLUDE)

.PHONY: all clean fclean re