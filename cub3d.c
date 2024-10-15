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
		"100000000000001110000000001",
		"1000001D1000001010000000001",
		"100000111000001D10000000001",
		"100000000000000000000000001",
		"100000000011111D11111000001",
		"100000001111100000011110001",
		"111111111111111111111111111",
		NULL
	};

	ft_memset(&data, 0, sizeof(t_cube));
	data.map = map;
	data.mlx = mlx_init(W_WIDHT, W_HEIGHT, "cub3d", 1);
	if (!data.mlx)
		printf("mlx_init");
	textures_init(NORTH_TEXTURE, data.tex_buf[0]);
	textures_init(SOUTH_TEXTURE, data.tex_buf[1]);
	textures_init(EAST_TEXTURE, data.tex_buf[2]);
	textures_init(WEAST_TEXTURE, data.tex_buf[3]);
	textures_init(DOOR_TEXTURE, data.tex_buf[4]);
	rerendere_map(&data);
	mlx_loop_hook(data.mlx, player_moves, &data);
	mlx_loop(data.mlx);
	return (0);
}
