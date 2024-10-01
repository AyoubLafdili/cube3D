/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:57:26 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/17 14:57:26 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "MLX42.h"
#include <stdbool.h>

#ifndef CUB3D_H
#define CUB3D_H
#define TILE_SIZE 60
#define WINDOW_HEIGHT (TILE_SIZE * 9)
#define WINDOW_WIDHT (TILE_SIZE * 7)
#define FOV (60 * (M_PI / 180))

typedef enum e_direction
{
	UP ,
	DOWN ,
	RIGHT ,
	LEFT,
	T_LEFT,
	T_RIGHT
}   t_direction;

typedef enum e_color
{
	RED = 0xFF0000FF,
	BLUE = 0x0727f7FF,
	BLACK = 0x000000FF,
	WHITE = 0xFFFFFFFF,
}   t_color;

typedef struct s_coordinates
{
	double x;
	double y;
}   t_crd;

typedef struct s_line
{
	t_crd   start;
	t_crd   end;
}   t_line;

typedef struct s_circle
{
	int radius;
	t_crd center;
}   t_circle;

typedef struct s_player
{
	t_crd	p_crd;
	t_line   line;
	t_circle circle;
	double		rt_angel;
}   t_player;

typedef struct s_rays
{
	bool is_vertical_hit;
	double	distance;
	t_crd	hit_crd;
}	t_ray;

typedef struct s_cube
{
	char **map;
	t_player player;
	mlx_image_t *map_i;
	t_ray rays[WINDOW_WIDHT];
	mlx_t *mlx;

}   t_cube;

void init_line(t_cube *data, t_line *line, double angle);
void player_moves(mlx_key_data_t keydata, void *param);
void draw_line(t_cube *data, t_line *ln);
void rerendere_map(t_cube *data);
void check_angel(double *angle);
void draw_circle(t_cube *data);
void ft_swap(double *x, double *y);
void draw_map(t_cube *data);
int ft_sign(int nb);

#endif