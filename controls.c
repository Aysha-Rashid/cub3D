/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:12:16 by rosman            #+#    #+#             */
/*   Updated: 2024/08/09 16:12:11 by rosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	rotate_angle(t_data *data, t_pix *vec, int flag)
{
	double	angle;
	double	vec_x_save;

	vec_x_save = vec->x;
	if (flag == 1)
		angle = -SPEED;
	else
		angle = SPEED;
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

// BONUS
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
		rotate_left(data);
		data->rot_left = 0;
	}
	else
	{
		data->rot_right = 1;
		rotate_right(data);
		data->rot_right = 0;
	}
	data->mouse = x;
	return (0);
}

void load_object_texture(t_data *data, t_object *obj, char *texture_path)
{
	// (void)texture_path;
	// int x = 50;
	// printf("&obj->width : %i\n, &obj->height : %i \n\n", obj->width, obj->height);
    obj->texture = mlx_xpm_file_to_image(data->mlx.mlx_ptr, texture_path, &obj->width, &obj->height);
	// printf("&obj->width : %i\n, &obj->height : %i \n\n", obj->width, obj->height);
    if (!obj->texture)
        exit_error("Failed to load object texture", data);
}

void place_object(t_object *obj, double x, double y)
{
    obj->x = x;
    obj->y = y;
	printf("y = %f\nx = %f\n\n", y, x);
}

void render_object(t_data *data, t_object *obj)
{
    int screen_x = (int)(obj->x * data->screen_width);
    int screen_y = (int)(obj->y * data->screen_height);

    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, obj->texture, screen_x, screen_y);
}


//

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
