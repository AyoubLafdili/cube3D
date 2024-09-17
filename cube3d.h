#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "MLX42.h"

# define BOX 60
# define WHITE "white.png"
# define BLACK "black.png"
# define FAIL 1
# define SUCSESS 0
#define WINDOW_HEIGHT BOX * 9
#define WINDOW_WIDHT BOX * 7

typedef struct s_player
{
    int px;
    int py;
    int rt_angel;
}t_player;

typedef struct s_cube
{
    char **map;
    t_player player;
    mlx_t *mlx;
    mlx_image_t *wall_i;
    mlx_image_t *space_i;
    mlx_image_t *player_i;
    mlx_texture_t *texture;
}t_cube;