NAME = test

CC = cc

REMOVE = rm -rf

LIBFT_DIR = ../lib/libft
MLX_DIR = ../lib/MLX42/build


INCLUDE = -I ../ -I ../lib/libft -I ../lib/MLX42/include/MLX42
LINKIN_LIB = -L ../lib/libft -lft -L ../lib/MLX42/build -lMLX42  -ldl -lglfw -pthread -lm

M_SRC = test_file.c

M_OBJECT = $(M_SRC:%.c=%.o)

all: $(LIBFT_DIR) $(MLX_DIR) $(NAME)

%.o: %.c
	$(CC) $(INCLUDE) -c $< -o $@

$(MLX_DIR):
		@printf "\033[1;32mMLX42 BUILDING ...\033[m\n"
		cd ../lib/MLX42; cmake -B build; make -sC build

$(LIBFT_DIR):
	@printf "\033[1;32mLIBFT BUILDING ...\033[m\n"
	@make -sC ../lib/libft


$(NAME): $(M_OBJECT)
	$(CC)  $< -o $@ $(LINKIN_LIB)

clean:
	make -C ../lib/libft clean
	$(REMOVE) $(M_OBJECT)

fclean: clean
	$(REMOVE) $(NAME)
	$(REMOVE) $(MLX_DIR)
re : fclean all

.PHONY: ../lib/libft clean