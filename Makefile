NAME=minishell
DEPS=libft/libft.a get_next_line/get_next_line.o
LIBFT_DIR=libft
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-Wall -Wextra -Werror -I . -I $(INCLUDES) -Ofast
ifdef COMPILER_ARGS
CFLAGS+= -D$(COMPILER_ARGS)
endif
CFILES=	ft_getenv.c		ft_setenv.c		ft_unsetenv.c	mini_cd.c		\
		mini_echo.c		mini_env.c		mini_launch.c	mini_pwd.c		\
		mini_setenv.c	mini_unsetenv.c	utils.c			main.c			\

OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(REL_DEPS) $(OBJ)
	@gcc $(CFLAGS) -o $(NAME) $^

$(REL_DEPS):
	@make -C $(dir $@)

build/%.o: %.c
	@mkdir -p build
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME);

clean fclean re::
	@for file in $(dir $(REL_DEPS)) ; do $(MAKE) -C $$file $@ ; done

clean::
	@rm -rf build/

fclean::
	@rm -rf $(NAME)

re:: fclean all

.PHONY: clean fclean re all $(REL_DEPS)