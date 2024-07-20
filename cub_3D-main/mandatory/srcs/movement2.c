/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:09:14 by mawad             #+#    #+#             */
/*   Updated: 2024/05/17 19:44:00 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_game *game)
{
	if (game->rot_left == FALSE)
		return ;
	rotate_angle(game, &(game->dir), 1);
	rotate_angle(game, &(game->cam_plane), 1);
	if (game->player_angle >= 6.28319)
		game->player_angle -= 6.28319;
	else if (game->player_angle < 0)
		game->player_angle += 6.28319;
}

void	rotate_right(t_game *game)
{
	if (game->rot_right == FALSE)
		return ;
	rotate_angle(game, &(game->dir), 0);
	rotate_angle(game, &(game->cam_plane), 0);
	if (game->player_angle >= 6.28319)
		game->player_angle -= 6.28319;
	else if (game->player_angle < 0)
		game->player_angle += 6.28319;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->move_up = TRUE;
	else if (keycode == A_KEY)
		game->move_left = TRUE;
	else if (keycode == S_KEY)
		game->move_down = TRUE;
	else if (keycode == D_KEY)
		game->move_right = TRUE;
	else if (keycode == L_ARROW)
		game->rot_left = TRUE;
	else if (keycode == R_ARROW)
		game->rot_right = TRUE;
	else if (keycode == ESC_KEY)
		ft_destroy(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->move_up = FALSE;
	else if (keycode == A_KEY)
		game->move_left = FALSE;
	else if (keycode == S_KEY)
		game->move_down = FALSE;
	else if (keycode == D_KEY)
		game->move_right = FALSE;
	else if (keycode == L_ARROW)
		game->rot_left = FALSE;
	else if (keycode == R_ARROW)
		game->rot_right = FALSE;
	return (0);
}

// int	key_hook_linux(int keycode, t_game *game)
// {
// 	if (keycode == W_KEY_LINUX)
// 	{
// 		if (check_valid_move(game, W_KEY_LINUX) == TRUE)
// 		{
// 			game->player_posx += (game->dir.x * 0.10);
// 			game->player_posy += (game->dir.y * 0.10);
// 		}
// 		ray_cast(game);
// 	}
// 	else if (keycode == A_KEY_LINUX)
// 	{
// 		if (check_valid_move(game, A_KEY_LINUX) == TRUE)
// 		{
// 			game->player_posx -= (-game->dir.y * 0.10);
// 			game->player_posy -= (game->dir.x * 0.10);
// 		}
// 		ray_cast(game);
// 	}
// 	else if (keycode == S_KEY_LINUX)
// 	{
// 		if (check_valid_move(game, S_KEY_LINUX) == TRUE)
// 		{
// 			game->player_posx -= (game->dir.x * 0.10);
// 			game->player_posy -= (game->dir.y * 0.10);
// 		}
// 		ray_cast(game);
// 	}
// 	else if (keycode == D_KEY_LINUX)
// 	{
// 		if (check_valid_move(game, D_KEY_LINUX) == TRUE)
// 		{
// 			game->player_posx += (-game->dir.y * 0.10);
// 			game->player_posy += (game->dir.x * 0.10);
// 		}
// 		ray_cast(game);
// 	}
// 	else if (keycode == L_ARROW_LINUX)
// 	{
// 		rotate_angle(game, &(game->dir), 1);
// 		rotate_angle(game, &(game->cam_plane), 1);
// 		ray_cast(game);
// 	}
// 	else if (keycode == R_ARROW_LINUX)
// 	{
// 		rotate_angle(game, &(game->dir), 0);
// 		rotate_angle(game, &(game->cam_plane), 0);
// 		ray_cast(game);
// 	}
// 	return (0);
// }