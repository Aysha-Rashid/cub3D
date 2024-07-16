/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:29:25 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/16 22:17:11 by ayal-ras         ###   ########.fr       */
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

void	read_map(int file, t_data *data)
{
	char	*line;

	data->coord->width = 0;
	data->coord->height = 0;
	line = get_next_line(file);
	while (line)
	{
		free(line);
		line = get_next_line(file);
		data->coord->height++;
	}
	free(line);
}

void	init(t_data *data, char *file_name)
{
	data->file = open(file_name, O_RDONLY);
	if (data->file == -1)
		exit_error(WRONG_FILE);
	// read_map(data->file, data);
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
		mlx.ptr = mlx_init();
		mlx.win = mlx_new_window(mlx.ptr, 1000, 1000, "cub3d");
		init(&data, argv[1]);
		mlx_key_hook(mlx.win, esc_key, &mlx);
		mlx_loop(mlx.ptr);
	}
}
