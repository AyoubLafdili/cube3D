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
# define MV_SPEED 5
# define NORTH_TEXTURE "textures/wall.png"
# define SOUTH_TEXTURE "textures/FLOOR_4A.PNG"
# define EAST_TEXTURE "textures/CONCRETE_4A.PNG"
# define WEAST_TEXTURE "textures/CONCRETE_3C.PNG"
# define DOOR_TEXTURE "textures/TEST_DOOR.png"

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
	T_WHITE = 0xFFFFFF50,
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
	bool	door_hit;
	double	distance;
	double	angle;
	t_crd	hit_crd;
}	t_ray;

typedef struct s_door
{
	t_crd	door_idxs;
	bool	be_open;
	bool	be_close;
	bool	is_open;
	bool	is_close;
	double	offset;
}	t_door;

typedef struct s_door_list
{
	t_door				door;
	struct s_door_list	*next;

}	t_door_lst;

typedef struct s_cube
{
	mlx_t		*mlx;
	char		**map;
	t_player	player;
	mlx_image_t	*_3d_map;
	mlx_image_t	*mini_map;
	t_ray		rays[W_WIDHT];
	t_ray		door_ray;
	t_door_lst	*head;
	uint32_t	tex_buf[5][CS][CS];
}	t_cube;

/********************** Ray-casting functions ************************/

void		cast_rays(t_cube *data);
t_crd		horz_intersect(t_cube *data, t_crd start, double ray_angle);
t_crd		vert_intersect(t_cube *data, t_crd start, double ray_angle);
char		hit_check(t_cube *data, t_crd inter, double angle, bool is_horz);
bool		is_door_hit(t_cube *data, t_crd hit, double angle, bool is_horz);
t_direction	ray_direction(double ray_angle, bool horz_check);
double		calc_distance(t_crd player, t_crd hit);
void		wall_height_reset(int *_start_y, int *_end_y);
void		rerendere_map(void *param);
void		_3d_rendering_(t_cube *data);
int			calc_offset(t_crd ray_hit, bool is_horz);
void		textures_init(char *path, uint32_t mtx[CS][CS]);
t_door_lst	*get_related_door(t_cube *data, t_crd ray);

/********************** key-events functions ***************************/

void		player_moves(void *param);
bool		check_next_wall(t_cube *data, int x, int y);
bool		check_next_door(t_cube *data, int x, int y);

/********************** Minimap functions ***************************/

void		mini_map(t_cube *data);
void		draw_circle(t_cube *data);
void		draw_line(t_cube *data, t_line *ln);

/********************** Door functions ******************************/

bool		add_to_list(t_cube *data, t_crd d_idx);
void		cast_ray_door(t_cube *data, t_ray *r_door);
void		door_lst_clear(t_door_lst **head);
void		open_door(t_door_lst *head);
void		close_door(t_door_lst *head);

/********************** utils functions ******************************/

void		swap_colors(t_color *x, t_color *y);
void		ft_swap(double *x, double *y);
void		check_angel(double *angle);
int			ft_sign(int nb);

#endif