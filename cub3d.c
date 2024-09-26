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

void rerendere_map(t_cube *data)
{
	mlx_delete_image(data->mlx, data->map_i);
	draw_map(data);
	draw_circle(data);
	draw_line(data, &data->player.line);
}

int main()
{
	t_cube data;
	char *map[] = { 
		"1111111",
		"1100111",
		"1000101",
		"1000001",
		"1010001",
		"1001001",
		"1000001",
		"10000W1",
		"1111111",
		NULL
		};
	ft_memset(&data, 0, sizeof(t_cube));
	data.map = map;
	data.mlx = mlx_init(WINDOW_WIDHT, WINDOW_HEIGHT, "cub3d", 1);
	if (!data.mlx)
	   printf("mlx_init");
	draw_map(&data);
	data.player.circle.center.x = data.player.p_crd.x;
	data.player.circle.center.y = data.player.p_crd.y;
	draw_circle(&data);
	draw_line(&data, &data.player.line);
	mlx_key_hook(data.mlx, player_moves, &data);
	mlx_loop(data.mlx);
	return (0);
}
