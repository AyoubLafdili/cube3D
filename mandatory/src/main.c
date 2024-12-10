/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:35:55 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/07 21:48:44 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	start_game(char *filename)
{
	t_cube			cube;

	cube.map = (t_map){0};
	cube.mt.colors[C] = -1;
	cube.mt.colors[F] = -1;
	cube.mlx = mlx_init(W_WIDHT, W_HEIGHT, "cub3d", false);
	if (!cube.mlx)
		return (ft_error("mlx", "failed!"));
	if (parse_file(&cube, filename) == FAILED)
		return (destroy_game(&cube, true), FAILED);
	cube.mt._3d_map = mlx_new_image(cube.mlx, W_WIDHT, W_HEIGHT);
	if (!cube.mt._3d_map)
		return (ft_error("mlx", EMNIF), destroy_game(&cube, true), FAILED);
	if (mlx_image_to_window(cube.mlx, cube.mt._3d_map, 0, 0) == FAILED)
		return (ft_error("mlx", EMITWF), destroy_game(&cube, true), FAILED);
	mlx_close_hook(cube.mlx, close_callback, &cube);
	mlx_loop_hook(cube.mlx, player_moves, &cube);
	mlx_loop_hook(cube.mlx, rerendere_map, &cube);
	mlx_loop(cube.mlx);
	return (SUCCESS);
}

static inline bool	is_valid_ext(char *path)
{
	return (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4) == 0);
}

int	main(int argc, char **argv)
{
	if (argc == 2 && is_valid_ext(argv[argc - 1]))
		return (start_game(argv[argc - 1]), EXIT_FAILURE);
	else
		return (ft_error("map", "missing [map].cub"), EXIT_FAILURE);
}
