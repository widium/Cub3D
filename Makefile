NAME = cub3d
UNAME = $(shell uname -s)

# === Flags and Compile === #
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -fsanitize=address

ifeq ($(UNAME), Darwin)
	OS = APPLE
	MLX_PATH = mlx/
	MLX_FLAGS = -Lmlx $(MLX_PATH)libmlx.a -framework OpenGL -framework AppKit
	MLX_INC = -Imlx
else
	OS = LINUX
	MLX_PATH = mlx_linux/
	MLX_FLAGS = -Lmlx_linux $(MLX_PATH)libmlx.a -L/usr/lib -Imlx_linux -lXext -lX11 -lz
	MLX_INC = -I/usr/include -Imlx_linux -O3
endif

# === Libft === #
LIBFT_PATH = libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

CFILES = \
		srcs/main.c \
		srcs/init.c \
		srcs/hook.c \
		srcs/parsing/parsing.c \
		srcs/parsing/collect_map.c \
		srcs/parsing/file_format.c \
		srcs/parsing/game_infos.c \
		srcs/parsing/tools.c \
		srcs/parsing/map_checker.c \
		srcs/parsing/player.c \
		srcs/video/window_init.c \
		srcs/video/video_init.c \
		srcs/engine/engine.c \
		srcs/engine/engine_tools.c \
		srcs/engine/raycasting.c \
		srcs/engine/draw.c \
		srcs/engine/motion.c

OBJECTS = $(CFILES:.c=.o)

all: subsystems $(NAME)

subsystems:
	@make -C $(MLX_PATH) all
	@make -C $(LIBFT_PATH) all

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@ 

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) $(MLX_FLAGS) $(LIBFT_LIB) -lm -o $(NAME) 

clean:
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

INPUT ?= $(shell bash -c 'read -p "PATH TO MAP: " input; echo $$input')
leaks:	all
	leaks -atExit -- ./$(NAME) $(INPUT)

valgrind:	all
	valgrind -q --leak-check=full ./$(NAME) $(INPUT)

.PHONY: all clean fclean re
