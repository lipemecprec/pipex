NAME = libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -fPIE
RM = rm -f
LIB = libft.h

SRCS =  ft_atoi.c	ft_bzero.c		ft_calloc.c		ft_isalpha.c	\
	ft_isalnum.c	ft_isascii.c	ft_isdigit.c	ft_isprint.c	\
	ft_strchr.c		ft_strdup.c		ft_strlcat.c	ft_strlcpy.c	\
	ft_strlen.c		ft_strrchr.c	ft_strncmp.c	ft_strnstr.c	\
	ft_memchr.c		ft_memcpy.c		ft_memset.c		ft_memmove.c	\
	ft_memcmp.c		ft_tolower.c	ft_toupper.c	ft_substr.c		\
	ft_strjoin.c	ft_strtrim.c	ft_split.c		ft_itoa.c		\
	ft_strmapi.c	ft_striteri.c	ft_putchar_fd.c	ft_putendl_fd.c	\
	ft_putnbr_fd.c	ft_putstr_fd.c	get_next_line.c \
	ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	\
	ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c	\
	ft_lstclear.c	ft_lstiter.c		ft_lstmap.c	\
	ft_atohex.c

OBJS = ${SRCS:%.c=%.o}

all: ${NAME}

${NAME}: ${OBJS} ${LIB}
	ar -rcs ${NAME} ${OBJS}

${OBJS}:
	${CC} -I . -c ${FLAGS} ${SRCS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

run: re
	${CC} ${FLAGS} -lbsd -g -Og -std=c99 main.c -lft -L . && ./a.out

so:
	${CC} -nostartfiles -fPIC ${FLAGS} ${SRCS} ${BONUSSRCS}
	gcc -nostartfiles -shared -o libft.so ${OBJS} ${BONUSOBJS}

.PHONY: all clear fclean re
