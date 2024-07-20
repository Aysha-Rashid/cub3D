/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 22:35:39 by mawad             #+#    #+#             */
/*   Updated: 2024/05/21 19:25:08 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

//game[i][j] game[y][x]

//cast the fraction as double whilst checking the range because
//otherwise, -1 to 0 range and 0 to 1 range would both be truncated
//to 0 and thus, this would make all the walls along the left edge
//(where x = 0) and all the walls along the top edge where y = 0)
//twice as thick.
void	ft_drawmap1(t_game *game, int i, int j)
{
	if (((double)i / MIN_MAP_SCALE) >= 0
		&& (((double)i / MIN_MAP_SCALE) < game->map_ind_height)
		&& (((double)j / MIN_MAP_SCALE) >= 0)
		&& (((double)j / MIN_MAP_SCALE) < game->map_ind_width))
	{
		if (game->map[i / MIN_MAP_SCALE][j / MIN_MAP_SCALE] == '1')
			my_pixel_put(game, game->minimap.x_draw,
				game->minimap.y_draw, 0xa4b1b9);
		else if (game->map[i / MIN_MAP_SCALE][j / MIN_MAP_SCALE] == 'X')
			my_pixel_put(game, game->minimap.x_draw,
				game->minimap.y_draw, 0x67828b);
		else
			my_pixel_put(game, game->minimap.x_draw,
				game->minimap.y_draw, 0xf7f9fb);
	}
	else
		my_pixel_put(game, game->minimap.x_draw,
			game->minimap.y_draw, 0x67828b);
}

void	draw_player(t_game *game)
{
	double	angle;
	double	begin_x;
	double	begin_y;
	int		i;

	angle = (game->player_angle * 180 / M_PI) + 30 - 90;
	while (angle >= (game->player_angle * 180 / M_PI) - 30 - 90)
	{
		i = 0;
		begin_x = 115;
		begin_y = 115;
		while (i < 20)
		{
			begin_x += cos(angle * M_PI / 180);
			begin_y += sin(angle * M_PI / 180);
			my_pixel_put(game, begin_x, begin_y, 0xAA4A44);
			i++;
		}
		angle -= 0.25;
	}
}

void	draw_border(t_game *game, int width, int height, int color)
{
	int	i;
	int	j;
	int	thickness;

	i = 0;
	thickness = 7;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if ((i >= 0 && i <= thickness)
				|| (i >= height - thickness && i <= height - 1)
				|| (j >= 0 && j <= thickness)
				|| (j >= width - thickness && j <= width - 1))
				my_pixel_put(game, j + 15, i + 15, color);
			j++;
		}
		i++;
	}
}

void	ft_minimap(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	j = game->player_posx * MIN_MAP_SCALE;
	i = game->player_posy * MIN_MAP_SCALE;
	x = j - 100;
	y = i - 100;
	game->minimap.y_draw = 15;
	while (y < i + 100)
	{
		x = j - 100;
		game->minimap.x_draw = 15;
		while (x < j + 100)
		{
			ft_drawmap1(game, y, x);
			x++;
			game->minimap.x_draw++;
		}
		game->minimap.y_draw++;
		y++;
	}
	draw_border(game, 200, 200, 0x000000);
	draw_player(game);
}
