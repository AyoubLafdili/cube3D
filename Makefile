# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/15 09:12:42 by aaitelka          #+#    #+#              #
#    Updated: 2024/10/24 00:08:51 by aaitelka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN := \033[0;32m
NC := \033[0m
LIBMLX := ./lib/MLX42
LIBFT := ./lib/libft
CC := cc #-g -fsanitize=address
CFLAGS := -Wall -Wextra -Werror -Ofast
NAME := cub3D
BONUS := cub3D_bonus

HEADS := -I ./include -I ./bonus/include -I $(LIBFT) -I $(LIBMLX)/include/MLX42
LIBS := $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -lglfw -ldl -pthread -lm -L"/Users/$(USER)/.brew/opt/glfw/lib/"

SRCS := src/main.c \
		src/parse/ft_array_utils.c \
		src/parse/ft_parse.c \
		src/parse/ft_parse_file.c \
		src/parse/ft_parse_utils.c \
		src/parse/ft_parse_map.c \
		src/parse/ft_map_utils.c \
		src/parse/ft_parse_color.c \
		src/parse/ft_parse_texture.c \
		src/parse/ft_utils.c \
		src/parse/ft_square_it.c \
		src/parse/ft_psp.c \
		src/error/ft_error.c \
		src/mini_map/draw_circle.c \
		src/mini_map/draw_line.c \
		src/mini_map/player_movement.c \
		src/ray_casting/ray_casting.c \
		src/ray_casting/intersection_calc.c \
		src/ray_casting/walls_drawing.c \
		src/ray_casting/utils.c \

OBJS := $(SRCS:%.c=%.o)

B_SRCS :=

B_OBJS := $(B_SRCS:%.c=%.o)

all: libft libmlx $(NAME)
# all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME) executable...$(NC)"
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

bonus: libft libmlx $(BONUS)

$(BONUS): $(B_OBJS) ./include/*.h
	@echo "$(GREEN)Linking $(BONUS) executable...$(NC)"
	$(CC) $(CFLAGS) $(B_OBJS) $(LIBS) -o $(BONUS)

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && \
	make -C $(LIBMLX)/build

%.o: %.c ./include/*.h
	@$(CC) $(CFLAGS) $(HEADS) -o $@ -c $<

%_bonus.o : %_bonus.c
	@$(CC) $(CFLAGS) $(HEADS) -o $@ -c $<
	
clean:
	@echo "$(GREEN)Cleaning...$(NC)"
	$(RM) $(OBJS)
	$(RM) $(B_OBJS)
#	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@echo "$(GREEN)Full Cleaning...$(NC)"
	$(RM) $(NAME) $(BONUS)
#	$(RM) -rf $(LIBMLX)/build
#	@$(MAKE) -C $(LIBFT) fclean

re: fclean all
