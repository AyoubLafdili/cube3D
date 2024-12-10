/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:28:11 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 23:00:37 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <libft.h>
# include <stdio.h>
# include <MLX42.h>
# include <fcntl.h>

# define EMFEMPTY "File is empty"
# define ETXAE "texture already exists"
# define EIFAIL "failed to load image"
# define ECNRGB "should be R,G,B format"
# define ECOOR "color has range [0, 255]"
# define ECCAE "ceiling already exists"
# define ECFAE "floor already exists"
# define EMAPNTF "missed map!"
# define EMAPHNL "has new line!"
# define EMAPCTB "contains tab!"
# define EMAPHIC "invalid character!"
# define EMAPHOS "has only spaces"
# define EMAPN33 "should be at least 3 x 3"
# define EPNTFND "player not found!"
# define EPMLFND "multiple players found!"
# define IN "error in "
# define EMNIF "new image failed!"
# define EMITWF "image to window failed!"
# define EAFTSI "failed to sqare it"

# define RD "\033[31m"
# define ORNG "\033[38;5;208m"
# define RS "\033[0m"

# define FAILED 	-1
# define SUCCESS 	0

# define EFEMPTY	30

# define CS			64
# define W_HEIGHT	1080
# define W_WIDHT	1920
# define RT_SPEED	2
# define MV_SPEED	20

typedef enum e_directions
{
	NO,
	EA,
	SO,
	WE,
	TXTRS_SZ
}	t_cardin;

typedef enum e_colors
{
	F,
	C,
	CLRS_SZ
}	t_colors;

typedef enum e_direction
{
	UP ,
	DOWN ,
	RIGHT ,
	LEFT,
	T_LEFT,
	T_RIGHT
}	t_direction;

typedef struct s_coordinates
{
	double			x;
	double			y;
}	t_crd;

typedef struct s_player
{
	double			fov;
	double			rt_angle;
	t_crd			crd;
}	t_player;

typedef struct s_rays
{
	bool			vert_hit;
	double			distance;
	double			angle;
	t_crd			hit_crd;
}	t_ray;

typedef struct s_material
{
	mlx_image_t		*_3d_map;
	mlx_image_t		*images[TXTRS_SZ];
	long			colors[CLRS_SZ];
	uint32_t		tex_buf[TXTRS_SZ][CS][CS];
}	t_material;

typedef struct s_map
{
	char			*content;
	char			**_2d;
	int				longest;
	int				size;
}	t_map;

typedef struct s_cube
{
	mlx_t			*mlx;
	t_player		player;
	t_map			map;
	t_material		mt;
	t_ray			rays[W_WIDHT];
}	t_cube;

/*================== PARSING =================*/

int				parse_file(t_cube *cube, char *filename);
int				ft_readfile(int fd, int f(t_cube *, char *), t_cube *cube);
int				ft_parse(t_cube *cube, char *line);
int				ft_parse_texture(t_cube *cube, char *line);
int				ft_parse_color(t_cube *cube, char *line);
int				ft_parse_map(t_cube *cube);
bool			materials_inited(t_material *material);
t_colors		colors_inited(t_material *material);
t_cardin		txtr_inited(t_material *material);
int				square_it(t_map *map);
void			init_player(t_cube *data, int x, int y);
bool			is_only(const char *line, const char c);
bool			is_blank(const char *line);
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
long			ft_atol(const char *str);

/*================== RAY CATSING =================*/

void			cast_rays(t_cube *data);
t_crd			horz_intersect(t_cube *data, t_crd start, double ray_angle);
t_crd			vert_intersect(t_cube *data, t_crd start, double ray_angle);
bool			hit_check(t_cube *data, t_crd inter, double angle, bool horz);
t_direction		ray_direction(double ray_angle, bool horz_check);
void			wall_height_reset(int *_start_y, int *_end_y);
int				_3d_rendering_(t_cube *data);
void			check_angel(double *angle);
void			ft_swap(double *x, double *y);
int				ft_sign(int nb);

/*================== HOOKS =================*/

void			player_moves(void *param);
void			mv_hdlr(t_cube *data, t_direction dir);
void			close_callback(void *param);
void			rerendere_map(void *param);
bool			check_next(char **map, int x, int y);

/*================== END =================*/

void			destroy_game(t_cube *cube, bool status);
void			ft_clear_array(char **array);
void			del_prev(t_cube *cube, t_cardin index);
int				ft_error(char *where, char *msg);
int				ft_maperror(char *where, int r, int c);

#endif
