/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:29:25 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/06 18:21:58 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_data(t_data *data, char *file_name)
{
	int	i;

	i = 0;
	data->file = open(file_name, O_RDONLY);
	if (data->file == -1)
		(ft_putendl_fd("Error", 2), ft_putendl_fd(WRONG_FILE, 2), exit(1));
	data->map_width = 0;
	data->map_height = 0;
	data->path_index = 0;
	data->image.texture[SO].img = NULL;
	data->image.texture[WE].img = NULL;
	data->image.texture[EA].img = NULL;
	data->image.texture[NO].img = NULL;
	data->image.ceiling = -1;
	data->image.floor = -1;
	data->map = NULL;
	data->player_angle = 0;
	while (i < 4)
		data->paths[i++] = NULL;
	read_map(data->file, data);
}


void	free_texture(t_data *data, int num)
{
	while (num >= 0)
		free(data->paths[num--]);
}

void	init_mlx(t_img_mlx mlx)
{
	mlx.bpp = 0;
	mlx.endian = 0;
	// mlx.mlx_ptr = NULL;
	// mlx.win_ptr = NULL;
	mlx.img_ptr = NULL;
	mlx.img_pixels_ptr = 0;
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
		data.screen_height = SCREEN_HEIGHT;
		data.screen_width = SCREEN_WIDTH;
		init_mlx(data.mlx);
		data.mlx.mlx_ptr = mlx_init();
		data.mlx.win_ptr = mlx_new_window(data.mlx.mlx_ptr, 1000,
				1000, "cub3d");
		data.mlx.img_ptr = mlx_new_image(data.mlx.mlx_ptr,
				data.screen_width, data.screen_height);
		if (data.mlx.img_ptr == NULL)
			return (printf("Error\nCouldn't allocate backdrop img ptr\n"), 1);
		data.mlx.img_pixels_ptr = (int *)
			mlx_get_data_addr(data.mlx.img_ptr,
				&(data.mlx.bpp), &(data.mlx.size_line),
				&(data.mlx.endian));
		if (data.mlx.img_pixels_ptr == NULL)
			return (printf("Error\nCouldn't allocate img pxl ptr\n"), 1);
		init_data(&data, argv[1]);
		init_view(&data);
		mlx_key_hook(data.mlx.win_ptr, esc_key, &data.mlx); // remember to call ft_dostory!!
		mlx_hook(data.mlx.win_ptr, 17, 0, ft_destroy, &data);
		// movement needs to done
		mlx_loop_hook(data.mlx.mlx_ptr, ray_cast, &data);
		mlx_loop(data.mlx.mlx_ptr);
	}
}
