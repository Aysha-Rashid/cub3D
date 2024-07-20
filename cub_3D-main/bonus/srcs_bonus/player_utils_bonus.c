/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:01:02 by mawad             #+#    #+#             */
/*   Updated: 2024/05/21 18:35:18 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	set_player_dir(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'N')
	{
		game->dir = (t_vector){0, -1};
		game->cam_plane = (t_vector){0.66, 0};
	}
	else if (game->map[y][x] == 'S')
	{
		game->dir = (t_vector){0, 1};
		game->cam_plane = (t_vector){-0.66, 0};
	}
	else if (game->map[y][x] == 'E')
	{
		game->dir = (t_vector){1, 0};
		game->cam_plane = (t_vector){0, 0.66};
	}
	else if (game->map[y][x] == 'W')
	{
		game->dir = (t_vector){-1, 0};
		game->cam_plane = (t_vector){0, -0.66};
	}
}

//This function sets up the players position attributes
//game->player_posx and game->player_posy and it also
//sets up the direction via the subcall to the
//set_plyaer_dir (function).
void	set_up_player(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				set_player_dir(game, x, y);
				game->player_posx = x + 0.5;
				game->player_posy = y + 0.5;
				game->player_count++;
			}
			x++;
		}
		y++;
	}
	if (game->player_count != 1)
		exit_err(game, NULL, "Must have strictly 1 player on map");
}
