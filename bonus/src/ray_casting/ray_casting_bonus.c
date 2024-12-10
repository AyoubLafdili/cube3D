/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:43:58 by alafdili          #+#    #+#             */
/*   Updated: 2024/11/08 18:57:27 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

t_crd	crd_dec(t_crd hit, double angle, bool is_horz)
{
	t_crd	new;

	new = hit;
	if (is_horz && ray_direction(angle, false) == UP)
		new.y--;
	if (!is_horz && ray_direction(angle, true) == LEFT)
		new.x--;
	return (new);
}

int	check_door(t_door_lst *door, int offset)
{
	if (!door)
		return (0);
	if (door->door.be_open)
	{
		if (offset < door->door.offset)
			return (0);
		else
			return (68);
	}
	else if (door->door.be_close)
	{
		if (offset > door->door.offset)
			return (68);
		else
			return (0);
	}
	if (door->door.is_close)
		return (68);
	else if (door->door.is_open && offset < CS - DOOR_LIMIT)
		return (0);
	return (68);
}

char	hit_check(t_cube *data, t_crd hit, double angle, bool is_horz)
{
	int	y;
	int	x;
	int	offset;

	hit = crd_dec(hit, angle, is_horz);
	y = hit.y / CS;
	x = hit.x / CS;
	if (x < 0 || x >= data->map.longest || y < 0 || y >= data->map.size)
		return (0);
	if (is_wall(data->map._2d[y][x]))
		return (1);
	if (is_door(data->map._2d[y][x]))
	{
		offset = calc_offset(hit, is_horz);
		return (check_door(get_rel_door(data, hit), offset));
	}
	return (0);
}

void	save_ray_attr(t_cube *data, t_crd horz, t_crd vert, t_ray *attr)
{
	double		h_d;
	double		v_d;
	t_player	player;

	player = data->player;
	h_d = calc_distance(player.circle.center, horz);
	v_d = calc_distance(player.circle.center, vert);
	if (h_d < v_d)
	{
		attr->distance = h_d * cos(attr->angle - player.rt_angle);
		attr->door_hit = is_dhit(data, horz, attr->angle, true);
		attr->vert_hit = false;
		attr->hit_crd = horz;
		return ;
	}
	attr->distance = v_d * cos (attr->angle - player.rt_angle);
	attr->door_hit = is_dhit(data, vert, attr->angle, false);
	attr->vert_hit = true;
	attr->hit_crd = vert;
}

void	cast_rays(t_cube *data)
{
	int		i;
	t_crd	horz;
	t_crd	vrtcl;
	double	ray_angle;

	i = 0;
	data->player.fov = 60 * M_PI / 180;
	ray_angle = data->player.rt_angle - (data->player.fov / 2);
	check_angel(&ray_angle);
	while (i < W_WIDHT)
	{
		check_angel(&ray_angle);
		data->rays[i].angle = ray_angle;
		horz = horz_intersect(data, data->player.circle.center, ray_angle);
		vrtcl = vert_intersect(data, data->player.circle.center, ray_angle);
		save_ray_attr(data, horz, vrtcl, &data->rays[i]);
		ray_angle += (data->player.fov / W_WIDHT);
		i++;
	}
}
