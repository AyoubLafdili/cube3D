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

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include "libft.h"
# include "MLX42.h"
# include <stdbool.h>

# define CS 64
# define W_HEIGHT 1000 
# define W_WIDHT 1800
# define RT_SPEED 2
# define MV_SPEED 2
# define NORTH_TEXTURE "textures/wall.png"
# define SOUTH_TEXTURE "textures/FLOOR_4A.PNG"
# define EAST_TEXTURE "textures/BRICK_4A.PNG"
# define WEAST_TEXTURE "textures/WOOD_1C.PNG"

typedef enum e_direction
{
	UP ,
	DOWN ,
	RIGHT ,
	LEFT,
	T_LEFT,
	T_RIGHT
}	t_direction;

typedef enum e_color
{
	RED = 0xFF0000FF,
	BLUE = 0x0727f7FF,
	BLACK = 0x000000FF,
	WHITE = 0xFFFFFFFF,
	T_WHITE = 0xFFFFFF90,
	SKY = 0x8FC2F4FF,
	FLOOR = 0x4B4C50FF
}	t_color;

typedef struct s_coordinates
{
	double	x;
	double	y;
}	t_crd;

typedef struct s_line
{
	t_crd	start;
	t_crd	end;
	int		lenght;
}	t_line;

typedef struct s_circle
{
	int		radius;
	t_crd	center;
}	t_circle;

typedef struct s_player
{
	double		fov;
	double		rt_angel;
	t_line		line;
	t_circle	circle;
}	t_player;

typedef struct s_rays
{
	bool	vert_hit;
	double	distance;
	double	angle;
	t_crd	hit_crd;
}	t_ray;


typedef struct s_cube
{
	mlx_t		*mlx;
	char		**map;
	t_player	player;
	mlx_image_t	*_3d_map;
	mlx_image_t	*mini_map;
	t_ray		rays[W_WIDHT];
	uint32_t	tex_buf[4][CS][CS];
}	t_cube;

bool		hit_check(char **map, t_crd intersept, double angle, bool is_horz);
t_crd		horz_intersect(t_cube *data, t_crd start, double ray_angle);
t_crd		vert_intersect(t_cube *data, t_crd start, double ray_angle);
t_direction	ray_direction(double ray_angle, bool horz_check);
t_direction	ray_direction(double ray_angle, bool horz_check);
void		textures_init(char *path, uint32_t mtx[CS][CS]);
void		wall_height_reset(int *_start_y, int *_end_y);
void		swap_colors(t_color *x, t_color *y);
void		draw_line(t_cube *data, t_line *ln);
void		ft_swap(double *x, double *y);
void		_3d_rendering_(t_cube *data);
void		rerendere_map(t_cube *data);
void		player_moves(void *param);
void		check_angel(double *angle);
void		draw_circle(t_cube *data);
void		cast_rays(t_cube *data);
void		mini_map(t_cube *data);
int			ft_sign(int nb);

#endif