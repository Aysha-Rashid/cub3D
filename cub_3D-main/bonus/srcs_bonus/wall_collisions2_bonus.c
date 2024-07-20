/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collisions2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:53:31 by mawad             #+#    #+#             */
/*   Updated: 2024/05/18 22:09:00 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	check_wc_right_helper(t_game *game, t_vector *target)
{
	if (check_right_of_horizontal(game))
	{
		if (game->dir.x >= 0)
			target->x = game->player_posx - MOVE_SPEED;
		else
			target->x = game->player_posx + MOVE_SPEED;
	}
	else
	{
		if (game->dir.x >= 0)
			target->x = game->player_posx + MOVE_SPEED;
		else
			target->x = game->player_posx - MOVE_SPEED;
	}
	target->y = game->player_posy;
}

void	check_wc_right(t_game *game)
{
	t_vector	target;

	if (mini_cast(game, D_KEY) == 0)
	{
		target.x = game->player_posx;
		if (check_right_of_vertical(game))
		{
			if (game->dir.y >= 0)
				target.y = game->player_posy + MOVE_SPEED;
			else
				target.y = game->player_posy - MOVE_SPEED;
		}
		else
		{
			if (game->dir.y >= 0)
				target.y = game->player_posy - MOVE_SPEED;
			else
				target.y = game->player_posy + MOVE_SPEED;
		}
	}
	else
		check_wc_right_helper(game, &target);
	check_valid_slide(game, target, 1);
}

static void	check_wc_left_helper(t_game *game, t_vector *target)
{
	if (check_right_of_horizontal(game))
	{
		if (game->dir.x >= 0)
			target->x = game->player_posx + MOVE_SPEED;
		else
			target->x = game->player_posx - MOVE_SPEED;
	}
	else
	{
		if (game->dir.x >= 0)
			target->x = game->player_posx - MOVE_SPEED;
		else
			target->x = game->player_posx + MOVE_SPEED;
	}
	target->y = game->player_posy;
}

void	check_wc_left(t_game *game)
{
	t_vector	target;

	if (mini_cast(game, A_KEY) == 0)
	{
		target.x = game->player_posx;
		if (check_right_of_vertical(game))
		{
			if (game->dir.y >= 0)
				target.y = game->player_posy - MOVE_SPEED;
			else
				target.y = game->player_posy + MOVE_SPEED;
		}
		else
		{
			if (game->dir.y >= 0)
				target.y = game->player_posy + MOVE_SPEED;
			else
				target.y = game->player_posy - MOVE_SPEED;
		}
	}
	else
		check_wc_left_helper(game, &target);
	check_valid_slide(game, target, 0);
}
