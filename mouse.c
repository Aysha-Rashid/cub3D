/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:28:50 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/09 18:29:19 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, t_data *data)
{
	int	prev_x;

	prev_x = data->mouse;
	if (x < 0 || x > data->screen_width - 1
		|| y < 0 || y > data->screen_height - 1)
		return (1);
	if (x == prev_x)
		return (1);
	if (x < prev_x)
	{
		data->rot_left = 1;
		rotate_left_n_right(data, data->rot_left, 1);
		data->rot_left = 0;
	}
	else
	{
		data->rot_right = 1;
		rotate_left_n_right(data, data->rot_right, 0);
		data->rot_right = 0;
	}
	data->mouse = x;
	return (0);
}
