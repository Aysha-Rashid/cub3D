/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:37:28 by mawad             #+#    #+#             */
/*   Updated: 2024/05/15 16:02:37 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	flush(t_game game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game.screen_height)
	{
		x = 0;
		while (x < game.screen_width)
		{
			my_pixel_put(&game, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	get_color(t_game *game, int index, int tex_x, int tex_y)
{
	int	color;
	int	offset;

	color = 0;
	offset = (game->album[index].tex_width * tex_y) + (tex_x);
	color = *(game->album[index].img_pixels_ptr + offset);
	return (color);
}

void	draw_v_line(t_game *game, t_dda dda, int x, int color)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	if (color == game->ceiling_color)
	{
		start = 0;
		end = dda.end;
	}
	else if (color == game->floor_color)
	{
		start = dda.start;
		end = game->screen_height - 1;
	}
	while (start < end)
	{
		my_pixel_put(game, x, start, color);
		start++;
	}
}

void	my_pixel_put(t_game *game, int x, int y, int color)
{
	int	offset;

	offset = (game->screen_width * y) + x;
	*(offset + game->data.img.img_pixels_ptr) = color;
}

// //Draws a square of dimensions (DIM * DIM) starting from the top-left corner
// //of the point specified by co-ordinates(x, y)
// void	draw_square(t_img *img, int x, int y, int color)
// {
// 	int	ylim;
// 	int	xlim;
// 	int	x_og;

// 	ylim = y + DIM - 2;
// 	xlim = x + DIM - 2;
// 	x_og = x + 2;

// 	while (y + 2 < ylim)
// 	{
// 		x = x_og;
// 		while (x < xlim)
// 		{
// 			my_pixel_put(img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_circle(t_img *img, int x, int y, int r)
// {
// 	int	x_inc;
// 	int	y_inc;
// 	int	decision;

// 	x_inc = r;
// 	y_inc = 0;
// 	decision = 1 - r;
// 	while (x_inc >= y_inc)
// 	{
// 		my_pixel_put(img, x + x_inc, y + y_inc, 0xFF0000);
// 		my_pixel_put(img, x + y_inc, y + x_inc, 0xFF0000);
// 		my_pixel_put(img, x - y_inc, y + x_inc, 0xFF0000);
// 		my_pixel_put(img, x - x_inc, y + y_inc, 0xFF0000);
// 		my_pixel_put(img, x - x_inc, y - y_inc, 0xFF0000);
// 		my_pixel_put(img, x - y_inc, y - x_inc, 0xFF0000);
// 		my_pixel_put(img, x + y_inc, y - x_inc, 0xFF0000);
// 		my_pixel_put(img, x + x_inc, y - y_inc, 0xFF0000);

// 		y_inc++;
// 		if (decision <= 0)
// 		{
// 			decision += 2 * y_inc + 1;
// 		}
// 		else
// 		{
// 			x_inc--;
// 			decision += 2 * (y_inc - x_inc) + 1;
// 		}
// 	}
// }

// void draw_line(t_img *img, t_vector start, t_vector end)
// {
// 	// end = (t_vector){(start.x + end.x) * DIM + DIM / 2,
// 		// (start.y + end.y) * DIM + DIM /2};
// 	// start = (t_vector){start.x * DIM + DIM /2, start.y * DIM + DIM /2};

// 	end = (t_vector){(start.x + end.x) * DIM, (start.y + end.y) * DIM};
// 	start = (t_vector){start.x * DIM, start.y * DIM};

// 	// printf("start.x is %f and start.y is %f\n", start.x, start.y);
// 	// printf("end.x is %f and end.y is %f\n", end.x, end.y);
// 	start.x = (int) start.x;
// 	start.y = (int) start.y;
// 	end.x = (int) end.x;
// 	end.y = (int) end.y;
// 	// printf("start.x is %f and start.y is %f\n", start.x, start.y);
// 	// printf("end.x is %f and end.y is %f\n", end.x, end.y);

// 	int dx = fabs(end.x - start.x);
//     int dy = fabs(end.y - start.y);
//     int sx = start.x < end.x ? 1 : -1;
//     int sy = start.y < end.y ? 1 : -1;
//     int err = dx - dy;
//     int e2;

//     while (!(start.x == end.x && start.y == end.y))
//     {
// 		// printf("-----------------------------------\n");
// 		// printf("start.x is %f and start.y is %f\n", start.x, start.y);
// 		// printf("end.x is %f and end.y is %f\n", end.x, end.y);
//         my_pixel_put(img, start.x, start.y, 0x4169E1);
//         e2 = 2 * err;
//         if (e2 > -dy)
//         {
//             err -= dy;
//             start.x += sx;
//         }
//         if (e2 < dx)
//         {
//             err += dx;
//             start.y += sy;
//         }
//     }
// 	// Ensure end point is drawn
//     my_pixel_put(img, start.x, start.y, 0x4169E1);
// }

// void	draw_walls(t_game game, t_img *img)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (game.map[y])
// 	{
// 		x = 0;
// 		while (game.map[y][x])
// 		{
// 			if (game.map[y][x] == '1')
// 				draw_square(img, x * DIM, y * DIM, 0xff00);
// 			else
// 				draw_square(img, x * DIM, y * DIM, 0xD3D3D3);
// 			x++;
// 		}
// 		y++;
// 	}
// }
