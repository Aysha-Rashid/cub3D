/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:34:12 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/11 18:28:04 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	tex->step = ((double) data->image.texture[index].fixed_height
			/ dda->line_height);
	tex->tex_pos = (dda->start - data->screen_height / 2 + 3
			* dda->line_height / 4) * tex->step;
	while (dda->start < dda->end)
	{
		tex->tex_y = (int) tex->tex_pos
			& (data->image.texture[index].fixed_height - 1);
		tex->tex_pos += tex->step;
		color = get_color(data, index, tex->tex_x, tex->tex_y);
		if (dda->side == 1)
			color = (color >> 1) & 8355711;
		offset = (data->screen_width * dda->start) + slice;
		*(data->mlx.img_pixels_ptr + offset) = color;
		dda->start++;
	}
}

void	calc_start_end(t_dda *dda, t_data *data)
{
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
	tex->tex_x = (int)(tex->wall_x * data->image.texture[0].fixed_width);
	if (dda->side == 0 && dda->ray_dir.x < 0)
		tex->tex_x = data->image.texture[0].fixed_width - (tex->tex_x + 1);
	if (dda->side == 1 && dda->ray_dir.y > 0)
		tex->tex_x = data->image.texture[0].fixed_width - (tex->tex_x + 1);
}
