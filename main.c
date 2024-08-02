/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:29:25 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/02 13:42:39 by ayal-ras         ###   ########.fr       */
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
	data->coord.width = 0;
	data->coord.height = 0;
	data->coord.x = 0;
	data->coord.y = 0;
	data->path_index = 0;
	data->image.texture[SO].img = NULL;
	data->image.texture[WE].img = NULL;
	data->image.texture[EA].img = NULL;
	data->image.texture[NO].img = NULL;
	data->image.ceiling = -1;
	data->image.floor = -1;
	data->map = NULL;
	while (i < 4)
		data->paths[i++] = NULL;
	read_map(data->file, data);
	close(data->file);
}

void	free_texture(t_data *data, int num)
{
	while (num >= 0)
		free(data->paths[num--]);
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
		free_texture(&data, 3);
		init_mlx(data.mlx);
		init_view(&data);
		mlx_key_hook(data.mlx.win, esc_key, &data.mlx);
		mlx_loop(data.mlx.ptr);
	}
}
