/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:26:01 by rosman            #+#    #+#             */
/*   Updated: 2024/08/06 21:06:24 by ayal-ras         ###   ########.fr       */
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

void	delta_dist(t_dda *dda)
{
	if (dda->ray_dir.x == 0.0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir.x);
	if (dda->ray_dir.y == 0.0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir.y);
}

void	side_dist(t_pix *pos, t_dda *dda)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (pos->x - dda->map.x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = ((1 - (pos->x - dda->map.x)) * dda->delta_dist_x);
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (pos->y - dda->map.y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (1 - (pos->y - dda->map.y)) * dda->delta_dist_y;
	}
}
void	init_dda_delta_side(t_data *data, t_dda *dda, int x, t_pix *ray_dir)
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
		if (data->map[(int)dda->map.y][(int)dda->map.x] == '1')
			dda->hit = 1;
	}
}

void	calc_start_end(t_dda *dda, t_data *data)
{
	(void)data;
	if (dda->side == 0)
	{
		dda->side_dist_x -= dda->delta_dist_x;
		dda->line_height = (int)(data->screen_height / dda->side_dist_x);
		dda->start = (data->screen_height / 2) - (dda->line_height / 2);
		if (dda->start < 0)
			dda->start = 0;
		dda->end = (data->screen_height / 2) + (dda->line_height / 4);
		if (dda->end > data->screen_height)
			dda->end = data->screen_height - 1;
	}
	else
	{
		dda->side_dist_y -= dda->delta_dist_y;
		dda->line_height = (int)(data->screen_height / dda->side_dist_y);
		dda->start = (data->screen_height / 2) - (dda->line_height / 2);
		if (dda->start < 0)
			dda->start = 0;
		dda->end = (data->screen_height / 2) + (dda->line_height / 4);
		if (dda->end > data->screen_height)
			dda->end = data->screen_height - 1;
	}
}

void	set_wall(t_data	*data, t_dda *dda, t_wall *tex)
{
	if (dda->side == 0)
	{
		tex->wall_x = data->player_y + dda->side_dist_x * dda->ray_dir.y;
		tex->wall_x -= floor(tex->wall_x);
	}
	else
	{
		tex->wall_x = data->player_x + dda->side_dist_y * dda->ray_dir.x;
		tex->wall_x -= floor(tex->wall_x);
	}
	tex->tex_x = (int)(tex->wall_x * data->image.texture[3].fixed_width);
	if (dda->side == 0 && dda->ray_dir.x < 0)
		tex->tex_x = data->image.texture[3].fixed_width - (tex->tex_x + 1);
	if (dda->side == 1 && dda->ray_dir.y > 0)
		tex->tex_x = data->image.texture[3].fixed_width - (tex->tex_x + 1);
}

static int	get_index(t_dda *dda)
{
	if (dda->side == 0 && dda->ray_dir.x > 0)
		return (1);
	if (dda->side == 0 && dda->ray_dir.x < 0)
		return (2);
	if (dda->side == 1 && dda->ray_dir.y > 0)
		return (3);
	if (dda->side == 1 && dda->ray_dir.y < 0)
		return (0);
	return (-1);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	int	offset;

	offset = (data->screen_width * y) + x;
	*(offset + data->mlx.img_pixels_ptr) = color;
}

int	get_color(t_data *data, int index, int x, int y)
{
	int	color;
	int	offset;

	color = 0;
	offset = (data->image.texture[index].fixed_width * y) + (x);
	color = *(data->image.texture[index].img_pixels_ptr + offset);
	return (color);
}

void	drawing_c_f(t_data *data, t_dda *dda, int slice, int color)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	if (color == data->image.ceiling)
	{
		start = 0;
		end = dda->end;
	}
	else if (color == data->image.floor)
	{
		start = dda->start;
		end = data->screen_height;
	}
	while (start < end)
	{
		my_pixel_put(data, slice, start, color);
		start++;
	}
}

void	drawing_walls(t_data *data, t_dda *dda, t_wall *tex, int slice)
{
	int	color;
	int	offset;
	int	index;

	index = get_index(dda);
	tex->step = ((double) data->image.texture[index].fixed_height / dda->line_height);
	tex->tex_pos = (dda->start - data->screen_height / 2 + 3
			* dda->line_height / 4) * tex->step;
	while (dda->start < dda->end)
	{
		tex->tex_y = (int) tex->tex_pos & (data->image.texture[index].fixed_height - 1);
		tex->tex_pos += tex->step;
		color = get_color(data, index, tex->tex_x, tex->tex_y);
		// printf("color : %d\n", color);
		// exit(0);
		// if (dda->side == 1)
		// 	color = (color >> 1) & 8355711;
		offset = (data->screen_width * dda->start) + slice;
		*(data->mlx.img_pixels_ptr + offset) = color;
		dda->start++;
	}
}

void	flush(t_data *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			my_pixel_put(game, x, y, 16777215);
			x++;
		}
		y++;
	}
}

int	ray_cast(void	*param)
{
	t_data	*data;
	t_dda	dda;
	t_wall	wall;
	t_pix	pos;
	int		slice;

	data = (t_data *) param;
	// movement
	flush(data);
	slice = -1;
	pos = (t_pix){data->player_x, data->player_y};
	while (++slice < data->screen_width)
	{
		init_dda_delta_side(data, &dda, slice, &(dda.ray_dir));
		side_dist(&pos, &dda);
		dda_algor(data, &dda);
		calc_start_end(&dda, data);
		set_wall(data, &dda, &wall);
		drawing_c_f(data, &dda, slice, data->image.ceiling);
		drawing_c_f(data, &dda, slice, data->image.floor);
		drawing_walls(data, &dda, &wall, slice);
	}
	return (mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr,
			data->mlx.img_ptr, 0, 0), 0);
	// return(0);
}
