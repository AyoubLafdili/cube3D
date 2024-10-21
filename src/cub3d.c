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

void	rerendere_map(void *param)
{
	t_cube	*data;

	data = (t_cube *)param;
	mlx_delete_image(data->mlx, data->mini_map);
	mlx_delete_image(data->mlx, data->_3d_map);
	mini_map(data);
	open_door(data->head);
	close_door(data->head);
	cast_rays(data);
	_3d_rendering_(data);
	mlx_set_instance_depth(data->mini_map->instances, 1);
	mlx_set_instance_depth(data->_3d_map->instances, 0);
}

bool	init_doors(t_cube *data)
{
	int		x;
	int		y;
	t_crd	idx;

	y = 0;
	while (y < 9)
	{
		x = 0;
		while (x < 28)
		{
			if (data->map[y][x] == 'D')
			{
				idx.x = x;
				idx.y = y;
				if (add_to_list(data, idx))
					return (EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

int	main()
{
	t_cube	data;
	char	*map[] = {
		"111111111111111111111111111",
		"100000000000000000000000001",
		"100000000000001111111111111",
		"1S000000000000DD00000000001",
		"100000000000001111111111111",
		"100000000000001000000000001",
		"100000000000001000000000001",
		"100000000000000000000000001",
		"111111111111111111111111111",
		NULL
	};

	ft_memset(&data, 0, sizeof(t_cube));
	data.map = map;
	data.head = NULL;
	data.mlx = mlx_init(W_WIDHT, W_HEIGHT, "cub3d", 1);
	if (!data.mlx)
		return (ft_putendl_fd("cub3d: mlx_init failed!", 2), EXIT_FAILURE);
	if (init_doors(&data))
	{
		door_lst_clear(&data.head);
		ft_putendl_fd("cub3d: allocation failed!", 2);
		return (EXIT_FAILURE);
	}
	textures_init(NORTH_TEXTURE, data.tex_buf[0]);
	textures_init(SOUTH_TEXTURE, data.tex_buf[1]);
	textures_init(EAST_TEXTURE, data.tex_buf[2]);
	textures_init(WEAST_TEXTURE, data.tex_buf[3]);
	textures_init(DOOR_TEXTURE, data.tex_buf[4]);
	mlx_loop_hook(data.mlx, rerendere_map, &data);
	mlx_loop_hook(data.mlx, player_moves, &data);
	mlx_loop(data.mlx);
	return (0);
}
