/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:34:22 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/09 18:29:16 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_left_right(t_data *data, t_pix *target_v, int flag)
{
	if (flag == A_KEY)
	{
		target_v->x -= (-data->view.y * (SPEED));
		target_v->y -= (data->view.x * (SPEED));
	}
	if (flag == D_KEY)
	{
		target_v->x += (-data->view.y * (SPEED));
		target_v->y += (data->view.x * (SPEED));
	}
	if (flag == W_KEY)
	{
		target_v->x += (data->view.x * (SPEED));
		target_v->y += (data->view.y * (SPEED));
	}
	if (flag == S_KEY)
	{
		target_v->x -= (data->view.x * (SPEED));
		target_v->y -= (data->view.y * (SPEED));
	}
}

int	check_valid_move(t_data *data, int flag)
{
	t_pix	target_v;

	target_v = (t_pix){data->player_x, data->player_y};
	check_left_right(data, &target_v, flag);
	if (data->map[(int) target_v.y][(int) target_v.x] == '1'
		|| data->map[(int) target_v.y][(int) target_v.x] == 'X')
		return (0);
	return (1);
}

void	move_up_n_down(t_data *data, int moves, int key)
{
	if (moves == 0)
		return ;
	if (check_valid_move(data, S_KEY) == 1 && key != 13)
	{
		data->player_x -= (data->view.x * SPEED);
		data->player_y -= (data->view.y * SPEED);
	}
	if (check_valid_move(data, key) == 1 && key != 1)
	{
		data->player_x += (data->view.x * SPEED);
		data->player_y += (data->view.y * SPEED);
	}
	if (check_valid_move(data, key) == 1 && key != D_KEY)
	{
		data->player_x -= (-data->view.y * SPEED);
		data->player_y -= (data->view.x * SPEED);
	}
	if (check_valid_move(data, key) == 1 && key != A_KEY)
	{
		data->player_x += (-data->view.y * SPEED);
		data->player_y += (data->view.x * SPEED);
	}
}

void	moving(t_data *data)
{
	move_up_n_down(data, data->move_down, S_KEY);
	move_up_n_down(data, data->move_up, W_KEY);
	move_up_n_down(data, data->move_right, D_KEY);
	move_up_n_down(data, data->move_left, A_KEY);
	rotate_left_n_right(data, data->rot_left, 1);
	rotate_left_n_right(data, data->rot_right, 0);
}
