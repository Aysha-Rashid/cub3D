/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:12:16 by rosman            #+#    #+#             */
/*   Updated: 2024/08/07 15:15:59 by rosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	rotate_angle(t_data *data, t_pix *vec, int flag)
{
	double	angle;
	double	vec_x_save;

	vec_x_save = vec->x;
	if (flag == 1)
		angle = -ROT_SPEED;
	else
		angle = ROT_SPEED;
	vec->x = cos(angle) * vec->x - sin(angle) * vec->y;
	vec->y = sin(angle) * vec_x_save + cos(angle) * vec->y;
	data->player_angle += angle / 2;
}

void	rotate_left(t_data *data)
{
	if (data->rot_left == 0)
		return ;
	rotate_angle(data, &(data->view), 1);
	rotate_angle(data, &(data->camera), 1);
	if (data->player_angle >= 6.28319)
		data->player_angle -= 6.28319;
	else if (data->player_angle < 0)
		data->player_angle += 6.28319;
}

void	rotate_right(t_data *data)
{
	if (data->rot_right == 0)
		return ;
	rotate_angle(data, &(data->view), 0);
	rotate_angle(data, &(data->camera), 0);
	if (data->player_angle >= 6.28319)
		data->player_angle -= 6.28319;
	else if (data->player_angle < 0)
		data->player_angle += 6.28319;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->move_up = 1;
	else if (keycode == A_KEY)
		data->move_left = 1;
	else if (keycode == S_KEY)
		data->move_down = 1;
	else if (keycode == D_KEY)
		data->move_right = 1;
	else if (keycode == L_ARROW)
		data->rot_left = 1;
	else if (keycode == R_ARROW)
		data->rot_right = 1;
	else if (keycode == ESC_KEY)
		ft_destroy(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W_KEY)
		data->move_up = 0;
	else if (keycode == A_KEY)
		data->move_left = 0;
	else if (keycode == S_KEY)
		data->move_down = 0;
	else if (keycode == D_KEY)
		data->move_right = 0;
	else if (keycode == L_ARROW)
		data->rot_left = 0;
	else if (keycode == R_ARROW)
		data->rot_right = 0;
	return (0);
}