
SRCS = src/main.c \
src/signal/ft_signal.c \
src/user_commands/excute_builtin/builtins/ft_cd.c \
src/user_commands/excute_builtin/builtins/ft_echo.c \
src/user_commands/excute_builtin/builtins/ft_env.c \
src/user_commands/excute_builtin/builtins/ft_exit.c \
src/user_commands/excute_builtin/builtins/ft_export.c \
src/user_commands/excute_builtin/builtins/ft_pwd.c \
src/user_commands/excute_builtin/builtins/ft_unset.c \
src/user_commands/excute_builtin/builtins/util_envp.c \
src/user_commands/excute_builtin/execute_builtin.c \
src/user_commands/execute_command.c \
src/user_commands/execute_program/execute_program.c \
src/user_commands/pipeline/pipeline.c \
src/user_commands/redirection/create_redirection_list.c \
src/user_commands/redirection/free_redirection_list.c \
src/util/env.c \
src/util/parse_command.c \
src/util/read_command_line.c \
src/util/split_command.c \
src/util/utils.c \
src/util/utils2.c \
src/util/check_quote.c

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

$(LIB_DIR)/$(LIB):
			make -C $(LIB_DIR)
clean:
			make -C $(LIB_DIR) clean
			$(RM) $(OBJS)

$(NAME):	$(OBJS) $(LIB_DIR)/$(LIB)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_DIR)/$(LIB)

fclean:		clean
			make -C $(LIB_DIR) fclean
			$(RM) $(NAME)
re:			fclean all

.PHONY:		all clean fclean re .c.o
