/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:35:51 by mawad             #+#    #+#             */
/*   Updated: 2024/05/18 22:09:00 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

//transparent pixels in mlx have color values that are less than 0.
//So we only copy the pixels that are non-transparent from the
//hand and gun sprite to the background image buffer.
void	draw_gun(t_game *game)
{
	int	color;
	int	offset;
	int	x;
	int	y;

	x = 0;
	while (x < game->screen_width - 1)
	{
		y = 0;
		while (y < game->screen_height - 1)
		{
			offset = (game->album[4].tex_width * y) + x;
			color = *(game->album[4].img_pixels_ptr + offset);
			if (color > 0)
				*(game->data.img.img_pixels_ptr + offset) = color;
			y++;
		}
		x++;
	}
}

void	draw_cross_hair(t_game *game)
{
	int	start;
	int	end;

	start = (game->screen_height / 2) - 20;
	end = (game->screen_height / 2) - 7;
	while (start < end)
		my_pixel_put(game, game->screen_width / 2, start++, 0x39FF14);
	start = (game->screen_height / 2) + 7;
	end = (game->screen_height / 2) + 20;
	while (start < end)
		my_pixel_put(game, game->screen_width / 2, start++, 0x39FF14);
	start = (game->screen_width / 2) - 20;
	end = (game->screen_width / 2) - 7;
	while (start < end)
		my_pixel_put(game, start++, game->screen_height / 2, 0x39FF14);
	start = (game->screen_width / 2) + 7;
	end = (game->screen_width / 2) + 20;
	while (start < end)
		my_pixel_put(game, start++, game->screen_height / 2, 0x39FF14);
}

void	draw_gun_sprite(t_game *game)
{
	draw_cross_hair(game);
	draw_gun(game);
}
