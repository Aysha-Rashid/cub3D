/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:29:25 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/09 22:04:20 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_data(t_data *data, char *file_name)
{
	int	i;

	i = 0;
	data->file = open(file_name, O_RDONLY);
	if (data->file == -1)
		(ft_putendl_fd("Error", 2), ft_putendl_fd(WRONG_FILE, 2), exit(0));
	data->map_width = 0;
	data->map_height = 0;
	data->path_index = 0;
	data->image.texture[SO].img = NULL;
	data->image.texture[WE].img = NULL;
	data->image.texture[EA].img = NULL;
	data->image.texture[NO].img = NULL;
	data->move_up = 0;
	data->move_down = 0;
	data->move_right = 0;
	data->move_left = 0;
	data->rot_left = 0;
	data->rot_right = 0;
	data->image.ceiling = -1;
	data->image.floor = -1;
	data->player_angle = 0;
	while (i < 4)
		data->paths[i++] = NULL;
	read_map(data->file, data);
}

void	init_mlx(t_data *data)
{
	data->mlx.mlx_ptr = mlx_init();
	data->mlx.win_ptr = mlx_new_window(data->mlx.mlx_ptr, data->screen_width,
			data->screen_height, "cub3d");
	data->mlx.img_ptr = mlx_new_image(data->mlx.mlx_ptr,
			data->screen_width, data->screen_height);
	if (data->mlx.img_ptr == NULL)
	{
		printf("Error\nCouldn't allocate backdrop img ptr\n");
		exit(0);
	}
	data->mlx.img_pixels_ptr = (int *) mlx_get_data_addr(data->mlx.img_ptr,
			&(data->mlx.bpp), &(data->mlx.size_line),
			&(data->mlx.endian));
	if (data->mlx.img_pixels_ptr == NULL)
	{
		printf("Error\nCouldn't allocate img pxl ptr\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.map = NULL;
	if (argc != 2)
		return (ft_putendl_fd(INVALID, 2), 1);
	if (argc > 1)
	{
		if (check_name(argv[1]))
			exit_error(WRONG_EXTEN, &data);
		data.screen_height = SCREEN_HEIGHT;
		data.screen_width = SCREEN_WIDTH;
		init_mlx(&data);
		init_data(&data, argv[1]);
		init_view(&data);
		mlx_hook(data.mlx.win_ptr, 2, 1L << 0, key_press, &data);
		mlx_hook(data.mlx.win_ptr, 3, 1L << 1, key_release, &data);
		mlx_hook(data.mlx.win_ptr, 6, 1L << 6, mouse_move, &data);
		mlx_hook(data.mlx.win_ptr, 17, 0, ft_destroy, &data);
		mlx_loop_hook(data.mlx.mlx_ptr, ray_cast, &data);
		mlx_loop(data.mlx.mlx_ptr);
	}
}
