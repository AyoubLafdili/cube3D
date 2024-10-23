/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:28:11 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/23 23:59:21 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3d_H
# define cub3d_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <libft.h>
# include <MLX42.h>

# define EMFEMPTY "File is empty"

# define ETXAE "texture already exists"
# define EIFAIL "failed to load image"
# define ECNRGB "should be R,G,B format"
# define ECOOR "color has range [0, 255]"
# define ECCAE "ceiling already exists"
# define ECFAE "floor already exists"

# define EMAPNTF "not found!"
# define EMAPHNL "has new line!"
# define EMAPCTB "contains tab!"
# define EMAPHIC "invalid character!"
# define EMAPHOS "has only spaces"
# define EMAPN33 "should be at least 3 x 3"

# define EPNTFND "player not found!"
# define EPMLFND "multiple players found!"

# define R3D "\033[31m"
# define ORNG "\033[38;5;208m"
# define RESET "\033[0m"

# define FAILED 	-1
# define SUCCESS 	0
# define FAILURE 	1

# define EFEMPTY	30
# define EMHASTAB	31

# define CS 64
# define W_HEIGHT 1000 
# define W_WIDHT 1800
# define RT_SPEED 2
# define MV_SPEED 8

typedef enum e_directions
{
	NO,
	EA,
	SO,
	WE,
	TXTRS_SZ
}	t_directions;

typedef enum e_colors
{
	F,
	C,
	CLRS_SZ
}	t_colors;

typedef struct s_point
{
	int				row;
	int				col;
}	t_point;


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

// typedef struct s_line
// {
// 	t_crd	start;
// 	t_crd	end;
// 	int		lenght;
// }	t_line;

// typedef struct s_circle
// {
// 	int		radius;
// 	t_crd	center;
// }	t_circle;

typedef struct s_player
{
	double		fov;
	double		rt_angel;
	t_crd 		crd;   //!this should be initted with position of player
	// t_line		line;
	// t_circle	circle;
}	t_player;

typedef struct s_rays
{
	bool	vert_hit;
	double	distance;
	double	angle;
	t_crd	hit_crd;
}	t_ray;

typedef struct s_map
{
	char			*content;
	char 			**_2d;
	size_t			longest;
	int				size;
	long			colors[CLRS_SZ];
	mlx_texture_t		*textures[TXTRS_SZ];
	t_point			point;
}	t_map;

typedef struct s_cube
{
	char			*content;
	mlx_t			*mlx;
	t_map			map;
	t_player				player;
	mlx_image_t				*mini_map;
	mlx_image_t				*_3d_map;
	t_ray					rays[W_WIDHT];
	uint32_t	tex_buf[4][CS][CS];
}	t_cube;

//* PARSE
int					parse_file(t_cube *cube, char *filename);
int					ft_readfile(int fd, int f(t_cube *, char *), t_cube *cube);
int					ft_parse(t_cube *cube, char *line);
int					ft_parse_texture(t_cube *cube, char *line);
int					ft_parse_color(t_cube *cube, char *line);
int					ft_parse_map(t_cube *cube);
bool				materials_inited(t_map *map);
t_colors			colors_inited(t_map *map);
t_directions		textures_inited(t_map *map);
int					square_it(t_map *map);
bool			is_only(const char *line, const char c);
bool			is_blank(const char *line);
bool			is_map(const char c);
bool			is_zero(const char c);
bool			is_space(const char c);
bool			is_player(const char c);
bool			is_newline(const char c);
bool			valid_char(const char c);
bool			is_wall(const char c);
bool			is_east(const char c);
bool			is_north(const char c);
bool			is_south(const char c);
bool			is_west(const char c);
bool			is_color(const char *line);
bool			is_texture(const char *line);
size_t				ft_array_size(char **array);
void				ft_clear_array(char **array, int size);
long				ft_atol(const char *str);
int					ft_error(char *where, char *msg);
//================== RAY CATSING =================//
bool				hit_check(t_cube *data, t_crd intersept, double angle, bool is_horz);
t_crd				horz_intersect(t_cube *data, t_crd start, double ray_angle);
t_crd				vert_intersect(t_cube *data, t_crd start, double ray_angle);
void				player_moves(void *param);
t_direction			ray_direction(double ray_angle, bool horz_check);
void				ft_swap(double *x, double *y);
void				rerendere_map(t_cube *data);
void				_3d_rendering_(t_cube *data);
void				wall_height_reset(int *_start_y, int *_end_y);
void				check_angel(double *angle);
void				cast_rays(t_cube *data);
int					ft_sign(int nb);

// void				draw_circle(t_cube *data);
// void				draw_line(t_cube *data, t_line *ln);
// void				mini_map(t_cube *data);
#endif
