CC = cc
NAME = fdf
CFLAGS = -Wall -Wextra -Werror -I ./includes
LIBFT = ./libft/libft.a

SRCS = main.c
OBJS = $(SRCS:.c=.o)

MLX = ./mlx_linux/libmlx.a
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib \
					 -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@make -C mlx_linux
	${CC} $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) $(LIBFT) $(MLX)

clean:
	@make clean -C libft
	rm -f $(OBJS)

fclean: clean
	@make clean -C mlx_linux
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
