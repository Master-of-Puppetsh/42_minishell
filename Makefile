
SRCS = $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)
OBJS = $(SRCS:.c=.o)
NAME = minishell
INCLUDE = include
LIB = libft.a
LIB_DIR = src/util/libft
RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -I $(INCLUDE)
all:		$(NAME)


$(LIB):
			make -C $(LIB_DIR)
clean:
			make -C $(LIB_DIR) clean
			$(RM) $(OBJS)

$(NAME):	$(OBJS) $(LIB)
			cp $(LIB_DIR)/$(LIB) $(NAME)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
			make clean

fclean:		clean
			make -C $(LIB_DIR) fclean
			$(RM) $(NAME)
re:			fclean all

.PHONY:		all clean fclean re .c.o
