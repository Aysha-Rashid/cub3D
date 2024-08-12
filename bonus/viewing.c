/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:26:01 by rosman            #+#    #+#             */
/*   Updated: 2024/08/11 17:52:05 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_view(t_data *data)
{
	int	x;
	int	y;

	x = data->player_x;
	y = data->player_y;
	if (data->map[y][x] == 'N')
		data->player_angle = N_D0;
	else if (data->map[y][x] == 'E')
		data->player_angle = E_D90;
	else if (data->map[y][x] == 'S')
		data->player_angle = S_D180;
	else if (data->map[y][x] == 'W')
		data->player_angle = W_D270;
}

void	init_dda_delta(t_data *data, t_dda *dda, double x, t_pix *ray_dir)
{
	dda->camera_x = (2 * x / data->screen_width) - 1;
	dda->side = 0;
	dda->hit = 0;
	ray_dir->x = data->view.x + data->camera.x * dda->camera_x;
	ray_dir->y = data->view.y + data->camera.y * dda->camera_x;
	dda->map.x = (int)data->player_x;
	dda->map.y = (int)data->player_y;
	delta_dist(dda);
}

void	dda_algor(t_data *data, t_dda *dda)
{
	while (dda->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map.x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map.y += dda->step_y;
			dda->side = 1;
		}
		if (data->map[(int) dda->map.y][(int) dda->map.x] == '1')
			dda->hit = 1;
	}
}

int	ray_cast(void	*param)
{
	t_data	*data;
	t_dda	dda;
	t_wall	wall;
	t_pix	pos;
	double	slice;

	data = (t_data *) param;
	flush(data);
	slice = -1;
	pos = (t_pix){data->player_x, data->player_y};
	while (++slice < data->screen_width)
	{
		init_dda_delta(data, &dda, slice, &(dda.ray_dir));
		side_dist(&pos, &dda);
		dda_algor(data, &dda);
		calc_start_end(&dda, data);
		set_wall(data, &dda, &wall);
		drawing_c_f(data, &dda, slice, data->image.ceiling);
		drawing_c_f(data, &dda, slice, data->image.floor);
		drawing_walls(data, &dda, &wall, slice);
	}
	moving(data);
	return (mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
			data->mlx.img_ptr, 0, 0), 0);
}
