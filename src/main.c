/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:35:55 by aaitelka          #+#    #+#             */
/*   Updated: 2024/10/24 00:09:48 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	destroty_game(t_cube *cube)
{
	ft_clear_array((char **)cube->map._2d, cube->map.size);
}

void	rerendere_map(t_cube *data)
{
	mlx_delete_image(data->mlx, data->mini_map);
	mlx_delete_image(data->mlx, data->_3d_map);
	cast_rays(data);
	_3d_rendering_(data);
	mlx_set_instance_depth(data->_3d_map->instances, 1);
}

static int	start_game(char *filename)
{
	t_cube			cube;

	cube.map = (t_map){0};
	cube.map.colors[C] = -1;
	cube.map.colors[F] = -1;
	if (parse_file(&cube, filename) == SUCCESS)
	{
		cube.mlx = mlx_init(W_WIDHT, W_HEIGHT, "cub3d", 1);
		//!ray casting begining
		//!should check mlx if failed!
		rerendere_map(&cube);
		mlx_loop_hook(cube.mlx, player_moves, &cube);
		mlx_loop(cube.mlx);
		//!ray casting end
	}
	destroty_game(&cube);
	return (SUCCESS);
}

static inline bool	is_valid_ext(char *path)
{
	return (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4) == 0);
}

void leak(){system("leaks cub3D");}
int	main(int argc, char **argv)
{
atexit(leak);
	if (argc == 2 && is_valid_ext(argv[argc - 1]))
		start_game(argv[argc - 1]);
	else
		ft_error("map", "missing [map].cub");
	return (EXIT_SUCCESS);
}
