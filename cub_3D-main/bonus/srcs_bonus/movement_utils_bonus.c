/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:24:00 by mawad             #+#    #+#             */
/*   Updated: 2024/05/18 22:09:00 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

//In each of the rotate_left and rotate_right functions,
//I call the the rotate_angle function twice. Once for the
//direcion vector of the player and once for the camera
//vector. So to prevent the player_angle from being doubled
//everytime the player looks to the left or right, I increment
//the player angle by half. That way, the player angle is
//incremented properly per single rotation.
void	rotate_angle(t_game *game, t_vector *vec, int flag)
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
	game->player_angle += angle / 2;
}

static void	check_up_down(t_game *game, t_vector *target_v, int flag)
{
	if (flag == W_KEY)
	{
		target_v->x += (game->dir.x * (MOVE_SPEED));
		target_v->y += (game->dir.y * (MOVE_SPEED));
	}
	if (flag == S_KEY)
	{
		target_v->x -= (game->dir.x * (MOVE_SPEED));
		target_v->y -= (game->dir.y * (MOVE_SPEED));
	}
}

static void	check_left_right(t_game *game, t_vector *target_v, int flag)
{
	if (flag == A_KEY)
	{
		target_v->x -= (-game->dir.y * (MOVE_SPEED));
		target_v->y -= (game->dir.x * (MOVE_SPEED));
	}
	if (flag == D_KEY)
	{
		target_v->x += (-game->dir.y * (MOVE_SPEED));
		target_v->y += (game->dir.x * (MOVE_SPEED));
	}
}

t_bool	check_valid_move(t_game *game, int flag)
{
	t_vector	target_v;

	target_v = (t_vector){game->player_posx, game->player_posy};
	check_up_down(game, &target_v, flag);
	check_left_right(game, &target_v, flag);
	if (game->map[(int) target_v.y][(int) target_v.x] == '1'
		|| game->map[(int) target_v.y][(int) target_v.x] == 'X')
		return (FALSE);
	return (TRUE);
}
