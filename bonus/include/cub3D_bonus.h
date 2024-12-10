/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:28:11 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/12 12:15:15 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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

# define EMAPNTF "not found!"
# define EMAPHNL "has new line!"
# define EMAPCTB "contains tab!"
# define EMAPHIC "invalid character!"
# define EMAPHOS "has only spaces"
# define EMAPN33 "should be at least 3 x 3"
# define EPNTFND "player not found!"
# define EPMLFND "multiple players found!"
# define IN ": error in "
# define EMNIF "new image failed!"
# define EMITWF "failed to put image"
# define EAFTSI "failed to sqare it"

# define RD "\033[31m"
# define ORNG "\033[38;5;208m"
# define RS "\033[0m"

# define FAILED 	-1
# define SUCCESS 	0
# define S_SIZE		46
# define EFEMPTY	30

# define CS			128
# define W_HEIGHT	1080
# define W_WIDHT	1920
# define RT_SPEED	4
# define MV_SPEED	40
# define DOOR_LIMIT	10
# define DEAD_ZONE	6
# define P2D_DIST 	250

typedef enum e_cardinals
{
	NO,
	EA,
	SO,
	WE,
	DO,
	TXTRS_SZ
}	t_cardin;

typedef enum e_color
{
	RED = 0xFF0000FF,
	BLUE = 0x0727f7FF,
	BLACK = 0x000000FF,
	T_WHITE = 0xFFFFFF80,
}	t_color;

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
	double				x;
	double				y;
}	t_crd;

typedef struct s_circle
{
	int					radius;
	t_crd				center;
}	t_circle;

typedef struct s_line
{
	t_crd				start;
	t_crd				end;
}	t_line;

typedef struct s_player
{
	double				fov;
	double				rt_angle;
	t_line				line;
	t_circle			circle;
}	t_player;

typedef struct s_rays
{
	bool				vert_hit;
	bool				door_hit;
	double				distance;
	double				angle;
	t_crd				hit_crd;
}	t_ray;

typedef struct s_minimap
{
	bool				sh_exp;
	int					sq_size;
	int					size;
	float				min_fact;
	t_crd				start;
	t_crd				i_pst;
}	t_mini;

typedef struct s_material
{
	int					sp_size;
	long				colors[CLRS_SZ];
	mlx_image_t			*_3d_map;
	mlx_image_t			*mini_img;
	mlx_image_t			*images[TXTRS_SZ];
	mlx_image_t			*sprites[S_SIZE];
	uint32_t			tex_buf[TXTRS_SZ][CS][CS];
}	t_material;

typedef struct s_map
{
	char				*content;
	char				**_2d;
	int					longest;
	int					size;
}	t_map;

typedef struct s_door
{
	t_crd				door_idxs;
	bool				be_open;
	bool				be_close;
	bool				is_open;
	bool				is_close;
	float				offset;
}	t_door;

typedef struct s_door_list
{
	t_door				door;
	struct s_door_list	*next;
}	t_door_lst;

typedef struct s_cube
{
	mlx_t				*mlx;
	t_map				map;
	t_door_lst			*head;
	t_player			player;
	t_ray				door_ray;
	t_mini				mini;
	t_material			mt;
	t_ray				rays[W_WIDHT];
	bool				should_animate;
}	t_cube;

/*================== PARSING =================*/

int				parse_file(t_cube *cube, char *filename);
int				ft_parse(t_cube *cube, char *line);
int				ft_parse_texture(t_cube *cube, char *line);
int				ft_parse_color(t_cube *cube, char *line);
int				ft_parse_map(t_cube *cube);
int				square_it(t_map *map);
t_colors		colors_inited(t_material *material);
t_cardin		txtr_inited(t_material *material);
bool			materials_inited(t_material *material);
void			init_player(t_cube *data, int x, int y);

/*================== UTILS =================*/

bool			is_only(const char *line, const char c);
bool			is_blank(const char *line);
bool			is_zero(const char c);
bool			is_space(const char c);
bool			is_player(const char c);
bool			is_newline(const char c);
bool			valid_char(const char c);
bool			is_wall(const char c);
bool			is_door(const char c);
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
char			hit_check(t_cube *data, t_crd hit, double angle, bool is_horz);
bool			is_dhit(t_cube *data, t_crd hit, double angle, bool is_horz);
t_direction		ray_direction(double ray_angle, bool horz_check);
double			calc_distance(t_crd player, t_crd hit);
void			wall_height_reset(int *_start_y, int *_end_y);
t_crd			crd_dec(t_crd hit, double angle, bool is_horz);
void			_3d_rendering_(t_cube *data);
int				calc_offset(t_crd ray_hit, bool is_horz);
t_door_lst		*get_rel_door(t_cube *data, t_crd ray);
t_crd			crd_dec(t_crd hit, double angle, bool is_horz);
float			get_offset(t_cube *data, int ray_idx);

/*================= key-events functions ==============*/

void			player_moves(void *param);
void			rerendere_map(void *param);
void			close_callback(void *param);
void			mv_hdlr(t_cube *data, t_direction dir);
bool			check_next_wall(t_cube *data, int x, int y);
bool			check_next_door(t_cube *data, int x, int y);
void			independent_keys(mlx_key_data_t data, void *param);
void			mouse_moves(double xpos, double ypos, void *param);

/*================= Minimap functions ==============*/

void			mini_map(t_cube *data);
void			draw_circle(t_cube *data);
void			draw_line(t_cube *data, t_line ln);

/*================= Door functions ==============*/

bool			init_doors(t_cube *data);
void			check_distance_to_door(t_cube *data);
bool			add_to_list(t_cube *data, t_crd d_idx);
void			cast_ray_door(t_cube *data, t_ray *r_door);
void			door_lst_clear(t_door_lst **head);
void			open_door(t_door_lst *head);
void			close_door(t_door_lst *head);

/*================== SPRITES =================*/

void			animate_sprite(void *param);
int				load_sprite(t_cube *cube);

/*================= Utils functions ==============*/

void			ft_swap(double *x, double *y);
void			check_angel(double *angle);
int				ft_sign(int nb);

/*================== END =================*/

void			ft_clear_array(char **array);	
int				ft_error(char *where, char *msg);
int				ft_maperror(char *where, int r, int c);
void			destroy_game(t_cube *cube, bool status);
void			del_prev(mlx_t *mlx, mlx_image_t *images[], t_cardin index);

#endif