CC = cc 
NAME = fdf 
LIBFT = ./libft/libft.a
MLX = ./mlx_linux/libmlx.a 

MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz 
CFLAGS = -Wall -Wextra -Werror -I ./includes -I ./mlx_linux 

SRCS = main.c get_next_line.c get_line_count.c
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	@make -C libft
	@make -C mlx_linux
	${CC} ${CFLAGS} ${MLX_FLAGS} ${OBJS} -o ${NAME} ${LIBFT} ${MLX}

clean:
	@make clean -C libft
	rm -f ${OBJS}

fclean: clean
	@make clean -C mlx_linux
	rm -f ${LIBFT}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
