/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:22:52 by alafdili          #+#    #+#             */
/*   Updated: 2024/09/17 13:22:52 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_direction ray_direction(double ray_angle, bool horz_check)
{
	if (horz_check && ray_angle > M_PI_2 && ray_angle < 3 * M_PI_2)
		return (LEFT);
	else if (horz_check  && (ray_angle > 3 * M_PI_2 || ray_angle < M_PI_2))
		return (RIGHT);
	if (ray_angle > M_PI && ray_angle < 2 * M_PI)
		return (UP);
	else
		return (DOWN);
}

bool is_hit_the_wall(char **map, t_crd intersept, double angle, bool is_horizontal)
{
	int y;
	int x;

	if (is_horizontal && angle > M_PI && angle < 2 * M_PI)
		intersept.y--;
	else if (!is_horizontal && angle > M_PI_2 && angle < 3 * M_PI_2)
		intersept.x--;
	y = intersept.y / TILE_SIZE;
	x = intersept.x / TILE_SIZE;
	if (map[y][x] == '1')
		return (true);
	return (false);
}

t_crd vertical_intersection(t_cube *data, t_player player, double ray_angle)
{
	t_crd intersept;
	t_crd delta;
	
	intersept.x = floor(player.circle.center.x / TILE_SIZE) * TILE_SIZE;
	if (ray_direction(ray_angle, true) == RIGHT)
		intersept.x += TILE_SIZE;
	intersept.y = player.circle.center.y + ((intersept.x - player.circle.center.x) * tan(ray_angle));
	delta.x = TILE_SIZE;
	if (ray_direction(ray_angle, true) == LEFT)
		delta.x = -delta.x;
	delta.y = delta.x * tan(ray_angle); 
	if (ray_direction(ray_angle, false) == UP && delta.y > 0)
		delta.y = -delta.y;
	if (ray_direction(ray_angle, false) == DOWN && delta.y < 0)
		delta.y = -delta.y;
	while (intersept.x >= 0 && intersept.x < WINDOW_WIDHT 
		&& intersept.y >= 0 && intersept.y < WINDOW_HEIGHT)
	{
		if (is_hit_the_wall(data->map, intersept, ray_angle, false))
			return (intersept);
		intersept.y += delta.y;
		intersept.x += delta.x;
	}
	return (intersept.x = __INT_MAX__, intersept.y = __INT_MAX__, intersept);
}

t_crd horizontal_intersection(t_cube *data, t_player player, double ray_angle)
{
	t_crd intersept;
	t_crd delta;

	intersept.y = floor(player.circle.center.y / TILE_SIZE) * TILE_SIZE;
	if (ray_direction(ray_angle, false) == DOWN)
		intersept.y += TILE_SIZE;
	intersept.x = player.circle.center.x + ((intersept.y - player.circle.center.y) / tan(ray_angle));
	delta.y = TILE_SIZE;
	if (ray_direction(ray_angle, false) == UP)
		delta.y = -delta.y;
	delta.x = delta.y / tan(ray_angle); 
	if (ray_direction(ray_angle, true) == LEFT && delta.x > 0)
		delta.x = -delta.x;
	if (ray_direction(ray_angle, true) == RIGHT && delta.x < 0)
		delta.x = -delta.x;
	while (intersept.x >= 0 && intersept.x < WINDOW_WIDHT 
		&& intersept.y >= 0 && intersept.y < WINDOW_HEIGHT)
	{
		if (is_hit_the_wall(data->map, intersept, ray_angle, true))
			return (intersept);
		intersept.y += delta.y;
		intersept.x += delta.x;
	}
	return (intersept.x = __INT_MAX__, intersept.y = __INT_MAX__, intersept);
}

void save_ray_attribute(t_crd player, t_crd horizontal, t_crd vertical, t_ray *attr)
{
	double h_d;
	double v_d;

	h_d = sqrt(pow(horizontal.x - player.x, 2.0) + pow(horizontal.y - player.y, 2.0));
	v_d = sqrt(pow(vertical.x - player.x, 2.0) + pow(vertical.y - player.y, 2.0));
	if (h_d < v_d)
	{
		attr->distance = h_d;
		attr->hit_crd = horizontal;
		attr->is_vertical_hit = false;
		return ;
	}
	attr->distance = v_d;
	attr->hit_crd = vertical;
	attr->is_vertical_hit = true;
}

void cast_rays(t_cube *data)
{
	int		i;
	t_crd	horz;
	t_crd	vrtcl;
	double	ray_angle;

	i = 0;
	ray_angle = data->player.rt_angel - (FOV / 2);
	check_angel(&ray_angle);
	while (i < WINDOW_WIDHT)
	{
		check_angel(&ray_angle);
		horz = horizontal_intersection(data, data->player, ray_angle);
		vrtcl = vertical_intersection(data, data->player, ray_angle);
		save_ray_attribute(data->player.circle.center, horz, vrtcl, &data->rays[i]);
		data->rays[i].distance *= cos(ray_angle - data->player.rt_angel);
		ray_angle += (FOV / WINDOW_WIDHT);
		i++;
	}
}

void walls_drawing(t_cube *data)
{
	double	distance_to_pp;
	double	wall_height;
	int		i;
	double	y;
	double end;

	i = 0;
	data->_3d_map = mlx_new_image(data->mlx, WINDOW_WIDHT, WINDOW_HEIGHT);
	distance_to_pp = (WINDOW_WIDHT / 2) / tan(FOV  / 2);
	while (i < WINDOW_WIDHT)
	{
		wall_height = TILE_SIZE * distance_to_pp / data->rays[i].distance;
		y = (WINDOW_HEIGHT / 2) - (wall_height / 2);
		end = (WINDOW_HEIGHT / 2) + (wall_height / 2);
		if (y < 0)
			y = 0;
		if (end > WINDOW_HEIGHT)
			end = WINDOW_HEIGHT;
		while (y < end)
			mlx_put_pixel(data->_3d_map, i, y++, WHITE);

		i++;
	}
	mlx_image_to_window(data->mlx, data->_3d_map, 0, 0);
}

void rerendere_map(t_cube *data)
{
	mlx_delete_image(data->mlx, data->mini_map);
	mlx_delete_image(data->mlx, data->_3d_map);
	cast_rays(data);
	// draw_map(data);
	// draw_circle(data);
	// while (i < WINDOW_WIDHT)
	// {
	// 	data->player.line.start = data->player.circle.center;
	// 	data->player.line.end = data->rays[i].hit_crd;
	// 	draw_line(data, &data->player.line);
	// 	i++;
	// }
	walls_drawing(data);
	mlx_set_instance_depth(data->_3d_map->instances, 1);
}

int main()
{
	t_cube data;
	char *map[] = { 
		"111111111111111111111111111",
		"1S0000000000000000000000001",
		"100000000010000000000000001",
		"100000000000001000000000001",
		"100000000000000100000000001",
		"100000000000000000000000001",
		"100000000000000000000000001",
		"100000000000000000000000001",
		"111111111111111111111111111",
		NULL
		};
	ft_memset(&data, 0, sizeof(t_cube));
	data.map = map;
	data.mlx = mlx_init(WINDOW_WIDHT, WINDOW_HEIGHT, "cub3d", 1);
	if (!data.mlx)
	   printf("mlx_init");
	data.player.rt_angel = M_PI_2;
	data.player.circle.center.x = TILE_SIZE + (TILE_SIZE / 2);
	data.player.circle.center.y = TILE_SIZE + (TILE_SIZE / 2);
	rerendere_map(&data);
	mlx_key_hook(data.mlx, player_moves, &data);
	mlx_loop(data.mlx);
	return (0);
}