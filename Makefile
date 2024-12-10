# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/26 15:05:31 by alafdili          #+#    #+#              #
#    Updated: 2024/11/08 18:54:36 by aaitelka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc

REMOVE = rm -rf

FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = lib/libft
MLX_DIR = lib/MLX42/build

LIB_INCLUDE =  -I$(LIBFT_DIR) -Ilib/MLX42/include/MLX42
M_INCLUDE = -Imandatory/include $(LIB_INCLUDE)
B_INCLUDE = -Ibonus/include $(LIB_INCLUDE)

GREEN = \033[32m
END = \033[0m

LINKIN_LIB = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lMLX42 -L/Users/$(USER)/.brew/opt/glfw/lib -lglfw

M_SRC = mandatory/src/main.c \
		mandatory/src/parse/ft_parse.c \
		mandatory/src/parse/ft_parse_file.c \
		mandatory/src/parse/ft_parse_utils.c \
		mandatory/src/parse/ft_parse_map.c \
		mandatory/src/parse/ft_map_utils.c \
		mandatory/src/parse/ft_parse_color.c \
		mandatory/src/parse/ft_parse_texture.c \
		mandatory/src/parse/ft_materials_utils.c \
		mandatory/src/parse/ft_square_it.c \
		mandatory/src/parse/ft_psp.c \
		mandatory/src/utils/ft_error.c \
		mandatory/src/utils/ft_cleaner.c \
		mandatory/src/hooks/hooks_func.c \
		mandatory/src/hooks/move_handler.c \
		mandatory/src/hooks/keys_check.c \
		mandatory/src/ray_casting/ray_casting.c \
		mandatory/src/ray_casting/intersection_calc.c \
		mandatory/src/ray_casting/walls_drawing.c \
		mandatory/src/ray_casting/utils.c \

B_SRC = bonus/main_bonus.c \
		bonus/src/parse/ft_parse_bonus.c \
		bonus/src/parse/ft_parse_file_bonus.c \
		bonus/src/parse/ft_parse_utils_bonus.c \
		bonus/src/parse/ft_parse_map_bonus.c \
		bonus/src/parse/ft_map_utils_bonus.c \
		bonus/src/parse/ft_parse_color_bonus.c \
		bonus/src/parse/ft_parse_texture_bonus.c \
		bonus/src/parse/ft_materials_utils_bonus.c \
		bonus/src/parse/ft_square_it_bonus.c \
		bonus/src/parse/ft_psp_bonus.c \
		bonus/src/parse/ft_load_animation_bonus.c \
		bonus/src/utils/ft_error_bonus.c \
		bonus/src/utils/ft_cleaner_bonus.c \
		bonus/src/hooks/keys_check_bonus.c \
		bonus/src/hooks/move_handler_bonus.c \
		bonus/src/hooks/mouse_hook_bonus.c \
		bonus/src/hooks/hooks_func_bonus.c \
		bonus/src/ray_casting/ray_casting_bonus.c \
		bonus/src/ray_casting/intersection_calc_bonus.c \
		bonus/src/ray_casting/walls_drawing_bonus.c \
		bonus/src/hooks/collisions_bonus.c \
		bonus/src/ray_casting/utils_bonus.c \
		bonus/src/mini_map/draw_circle_bonus.c \
		bonus/src/mini_map/draw_line_bonus.c \
		bonus/src/mini_map/mini_map_bonus.c \
		bonus/src/doors/close_door_bonus.c \
		bonus/src/doors/door_lst_bonus.c \
		bonus/src/doors/door_ray_casting_bonus.c \
		bonus/src/doors/open_door_bonus.c \
		bonus/src/ray_casting/ray_casting_utils.c \
		bonus/src/doors/init_doors_bonus.c \

M_OBJECT = $(M_SRC:%.c=%.o)
B_OBJECT = $(B_SRC:%.c=%.o)


mandatory/%.o: mandatory/%.c mandatory/include/cub3D.h 
	$(CC) $(FLAGS) $(M_INCLUDE) -c $< -o $@

bonus/%.o: bonus/%.c bonus/include/cub3D_bonus.h
	$(CC) $(FLAGS) $(B_INCLUDE) -c $< -o $@

all: $(LIBFT_DIR) $(MLX_DIR) $(NAME) 

bonus: $(LIBFT_DIR) $(MLX_DIR) $(BONUS_NAME)

$(LIBFT_DIR):
	@printf "$(GREEN)LIBFT BUILDING ...$(END)\n"
	@make -C lib/libft

$(MLX_DIR):
		@printf "$(GREEN)MLX42 BUILDING ...$(END)\n"
		cd lib/MLX42; cmake -B build; make -sC build

$(NAME): $(M_OBJECT) $(LIBFT_DIR)/libft.a
	$(CC) $(FLAGS) $(M_OBJECT) -o $@ $(LINKIN_LIB)

$(BONUS_NAME): $(B_OBJECT) $(LIBFT_DIR)/libft.a
	$(CC) $(FLAGS) $(B_OBJECT) -o $@ $(LINKIN_LIB)

clean:
	make -C lib/libft clean
	$(REMOVE) $(M_OBJECT)
	$(REMOVE) $(B_OBJECT)

fclean: clean
	make -C lib/libft fclean
	$(REMOVE) $(NAME)
	$(REMOVE) $(BONUS_NAME)
	$(REMOVE) $(MLX_DIR)

re : fclean all

.PHONY: $(LIBFT_DIR) clean