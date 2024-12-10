/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:35:55 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/08 18:58:12 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	init_game(t_cube *cube)
{
	cube->map = (t_map){0};
	cube->mt = (t_material){0};
	cube->mt.colors[C] = -1;
	cube->mt.colors[F] = -1;
	cube->should_animate = false;
	cube->mlx = mlx_init(W_WIDHT, W_HEIGHT, "cub3d", false);
	if (!cube->mlx)
		return (ft_error("mlx", "failed!"), EXIT_FAILURE);
	return (SUCCESS);
}

static int	start_game(t_cube *cube, char *filename)
{
	if (init_game(cube) != SUCCESS)
		return (EXIT_FAILURE);
	if (parse_file(cube, filename) == FAILED)
		return (FAILED);
	if (load_sprite(cube) != SUCCESS)
		return (FAILED);
	cube->mt._3d_map = mlx_new_image(cube->mlx, W_WIDHT, W_HEIGHT);
	cube->mt.mini_img = mlx_new_image(cube->mlx, 200, 200);
	if (!cube->mt._3d_map || !cube->mt.mini_img)
		return (ft_error("mlx", "failed to create new image"));
	if (mlx_image_to_window(cube->mlx, cube->mt._3d_map, 0, 0) == FAILED
		|| mlx_image_to_window(cube->mlx, cube->mt.mini_img, 0, 0) == FAILED)
		return (ft_error("mlx", "failed to put image"));
	mlx_close_hook(cube->mlx, close_callback, cube);
	mlx_key_hook(cube->mlx, independent_keys, cube);
	mlx_cursor_hook(cube->mlx, mouse_moves, cube);
	mlx_loop_hook(cube->mlx, player_moves, cube);
	mlx_loop_hook(cube->mlx, animate_sprite, cube);
	mlx_loop_hook(cube->mlx, rerendere_map, cube);
	mlx_loop(cube->mlx);
	return (SUCCESS);
}

static inline bool	is_valid_ext(char *path)
{
	return (ft_strncmp(path + ft_strlen(path) - 4, ".cub", 4) == 0);
}

int	main(int argc, char **argv)
{
	t_cube			cube;

	if (argc != 2 && !is_valid_ext(argv[argc - 1]))
		return (ft_error("map", "missing [map].cub"), EXIT_FAILURE);
	if (start_game(&cube, argv[argc - 1]) == FAILED)
		destroy_game(&cube, EXIT_FAILURE);
	return (EXIT_FAILURE);
}
