/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collisions1_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:40:02 by mawad             #+#    #+#             */
/*   Updated: 2024/05/18 22:09:00 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	check_wc_up(t_game *game)
{
	t_vector	target;

	if (mini_cast(game, W_KEY) == 0)
	{
		target.x = game->player_posx;
		if (game->dir.y >= 0)
			target.y = game->player_posy + MOVE_SPEED;
		else
			target.y = game->player_posy - MOVE_SPEED;
		check_valid_slide(game, target, 0);
	}
	else
	{
		if (game->dir.x >= 0)
			target.x = game->player_posx + MOVE_SPEED;
		else
			target.x = game->player_posx - MOVE_SPEED;
		target.y = game->player_posy;
		check_valid_slide(game, target, 1);
	}
}

void	check_wc_down(t_game *game)
{
	t_vector	target;

	if (mini_cast(game, S_KEY) == 0)
	{
		target.x = game->player_posx;
		if (game->dir.y >= 0)
			target.y = game->player_posy - MOVE_SPEED;
		else
			target.y = game->player_posy + MOVE_SPEED;
		check_valid_slide(game, target, 0);
	}
	else
	{
		if (game->dir.x >= 0)
			target.x = game->player_posx - MOVE_SPEED;
		else
			target.x = game->player_posx + MOVE_SPEED;
		target.y = game->player_posy;
		check_valid_slide(game, target, 1);
	}
}
