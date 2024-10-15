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

void	rerendere_map(t_cube *data)
{
	mlx_delete_image(data->mlx, data->mini_map);
	mlx_delete_image(data->mlx, data->_3d_map);
	mini_map(data);
	cast_rays(data);
	_3d_rendering_(data);
	mlx_set_instance_depth(data->mini_map->instances, 1);
	mlx_set_instance_depth(data->_3d_map->instances, 0);
}


int	main()
{
	t_cube	data;
	char	*map[] = {
		"111111111111111111111111111",
		"1S0000000000000000000000001",
		"100000000010000000000000001",
		"100000000000001000000000001",
		"100000000000000100000000001",
		"100000000000000000000000001",
		"100000000000111111000000001",
		"1000000011111     110000001",
		"111111111111111111111111111",
		NULL
	};

	ft_memset(&data, 0, sizeof(t_cube));
	data.map = map;
	data.mlx = mlx_init(W_WIDHT, W_HEIGHT, "cub3d", 1);
	if (!data.mlx)
		printf("mlx_init");
	textures_init(NORTH_TEXTURE, data.mtx_n);
	textures_init(SOUTH_TEXTURE, data.mtx_s);
	textures_init(EAST_TEXTURE, data.mtx_e);
	textures_init(WEAST_TEXTURE, data.mtx_w);
	rerendere_map(&data);
	mlx_loop_hook(data.mlx, player_moves, &data);
	mlx_loop(data.mlx);
	return (0);
}
