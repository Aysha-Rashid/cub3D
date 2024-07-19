/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:29:25 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/19 14:05:07 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// display different wall textures, that vary depending on which side the wall is facing
// (NORTH, SOUTH, EAST, WEST)
// set the floor and the ceiling colors to two different ones
// 
// keyboard (keyhooks)
// 1. left and right arrow must allow to look left and right
// 2. W, A, S, and D allows you to move the point of view.
// 3. ESC exits the window
// 4. red cross close the window
// 5. images of the minilibx is imp.

// first argument takes the scene description with .cub extension
// 6 possible characters: 0 for emp, 1 for wall, N, S, W, E for the player's starting point.
// 

#include "cub3D.h"
#include "minilibx/mlx.h"
#include <string.h>

void	init_data(t_data *data, char *file_name)
{
	data->file = open(file_name, O_RDONLY);
	if (data->file == -1)
		exit_error(WRONG_FILE);
	data->coord.width = 0;
	data->coord.height = 0;
	data->coord.x = 0;
	data->coord.y = 0;
	read_map(data->file, &data->coord);
	close(data->file);
}

void	init_mlx(t_mlx mlx)
{
	mlx.bpp = 0;
	mlx.endian = 0;
	mlx.img = 0;
	mlx.ptr = 0;
	mlx.size_line = 0;
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_data	data;

	if (argc != 2)
		exit_error(INVALID);
	if (argc > 1)
	{
		if (check_name(argv[1]))
			exit_error(WRONG_EXTEN);
		init_data(&data, argv[1]);

		mlx.ptr = mlx_init();
		mlx.win = mlx_new_window(mlx.ptr, 1000, 1000, "cub3d");
		init_mlx(mlx);
		mlx_key_hook(mlx.win, esc_key, &mlx);
		mlx_loop(mlx.ptr);
	}
}


// map are not parsing with spaces rather they are parse by each digit (remove spaces in between each other).
// eg : if map is = 1 1 1 1 (this is valid) so is 1111 (this is also alright) so is 1211 (this is also correct)
