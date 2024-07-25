/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:29:25 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/24 16:22:57 by ayal-ras         ###   ########.fr       */
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

void	init_data(t_data *data, char *file_name)
{
	data->file = open(file_name, O_RDONLY);
	if (data->file == -1)
		(ft_putendl_fd("Error", 2), ft_putendl_fd(WRONG_FILE, 2), exit(1));
	data->coord.width = 0;
	data->coord.height = 0;
	data->coord.x = 0;
	data->coord.y = 0;
	data->image.texture[SO].img = NULL;
	data->image.texture[WE].img = NULL;
	data->image.texture[EA].img = NULL;
	data->image.texture[NO].img = NULL;
	data->image.ceiling = -1;
	data->image.floor = -1;
	data->map = NULL;
	read_map(data->file, data);
	close(data->file);
}

void check_texture(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
		printf("Texture %d: %p\n", i, data->image.texture[i].img);
        j = i + 1;
        while (j < 4)
        {
            if (data->image.texture[i].img == data->image.texture[j].img)
            {
                printf("same: i = %i, j = %i\n", i, j);
                exit(1); // Exit with an error if two textures are the same
            }
            j++;
        }
        i++;
    }
    printf("All textures are different\n");
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
	t_data	data;

	if (argc != 2)
		return (ft_putendl_fd(INVALID, 2), 1);
	if (argc > 1)
	{
		if (check_name(argv[1]))
			exit_error(WRONG_EXTEN, &data);

		data.mlx.ptr = mlx_init();
		data.mlx.win = mlx_new_window(data.mlx.ptr, 1000, 1000, "cub3d");
		init_data(&data, argv[1]);
		init_mlx(data.mlx);
		mlx_key_hook(data.mlx.win, esc_key, &data.mlx);
		mlx_loop(data.mlx.ptr);
	}
}


// map are not parsing with spaces rather they are parse by each digit (remove spaces in between each other).
// eg : if map is = 1 1 1 1 (this is valid) so is 1111 (this is also alright) so is 1211 (this is also correct)
