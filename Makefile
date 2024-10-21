NAME = cub3d

CC = cc

REMOVE = rm -rf

FLAGS = -Wall -Wextra -g -fsanitize=address

LIBFT_DIR = lib/libft
MLX_DIR = lib/MLX42/build


INCLUDE = -I lib/libft -Ilib/MLX42/include/MLX42
LINKIN_LIB = -Llib/libft -lft -Llib/MLX42/build -lMLX42 -L/Users/$(USER)/.brew/opt/glfw/lib -lglfw

M_SRC = src/cub3d.c src/player_movement.c mini_map/draw_circle.c mini_map/draw_line.c utils/utils.c \
		mini_map/mini_map.c ray_casting/ray_casting.c ray_casting/intersection_calc.c \
		ray_casting/walls_drawing.c ray_casting/texture_init.c doors/open_door.c doors/door_lst.c \
		src/collisions.c doors/door_ray_casting.c doors/close_door.c utils/ray_casting_utils.c

M_OBJECT = $(M_SRC:%.c=%.o)

all: $(LIBFT_DIR) $(MLX_DIR) $(NAME)

%.o: %.c cub3d.h
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(MLX_DIR):
		@printf "\033[1;32mMLX42 BUILDING ...\033[m\n"
		cd lib/MLX42; cmake -B build; make -sC build

$(LIBFT_DIR):
	@printf "\033[1;32mLIBFT BUILDING ...\033[m\n"
	@make -sC lib/libft


$(NAME): $(M_OBJECT)
	$(CC) $(FLAGS) $(M_OBJECT) -o $@ $(LINKIN_LIB)

clean:
	make -C lib/libft clean
	$(REMOVE) $(M_OBJECT)

fclean: clean
	make -C lib/libft fclean
	$(REMOVE) $(NAME)
	$(REMOVE) $(MLX_DIR)

re : fclean all

.PHONY: lib/libft clean