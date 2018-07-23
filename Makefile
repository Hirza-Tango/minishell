NAME=minishell
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I. -I libft -Ofast
CFILES=	ft_getenv.c		ft_setenv.c		ft_unsetenv.c	mini_cd.c		\
		mini_echo.c		mini_env.c		mini_launch.c	mini_pwd.c		\
		mini_setenv.c	mini_unsetenv.c	homestring.c					\

OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(OBJ) main.c libft/libft.a
	@gcc $(CFLAGS) -o $(NAME) $^

libft/libft.a:
	@make -C libft

build/%.o: %.c
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME);

clean:
	@make -C libft clean
	@rm -rf build/
 
fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all libft/libft.a