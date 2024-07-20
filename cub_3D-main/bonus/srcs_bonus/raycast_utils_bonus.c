/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:56:01 by mawad             #+#    #+#             */
/*   Updated: 2024/05/25 19:39:02 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	set_up_start_end(t_game *game, t_dda *dda)
{
	if (dda->side == 0)
	{
		dda->side_dist_x -= dda->delta_dist_x;
		dda->line_height = (int)(game->screen_height / dda->side_dist_x);
		dda->start = (game->screen_height / 2) - (3 * dda->line_height / 4);
		if (dda->start < 0)
			dda->start = 0;
		dda->end = (game->screen_height / 2) + (dda->line_height / 4);
		if (dda->end > game->screen_height)
			dda->end = game->screen_height - 1;
	}
	else
	{
		dda->side_dist_y -= dda->delta_dist_y;
		dda->line_height = (int)(game->screen_height / dda->side_dist_y);
		dda->start = (game->screen_height / 2) - (3 * dda->line_height / 4);
		if (dda->start < 0)
			dda->start = 0;
		dda->end = (game->screen_height / 2) + (dda->line_height / 4);
		if (dda->end > game->screen_height)
			dda->end = game->screen_height - 1;
	}
}

void	set_up_tex_x(t_game *game, t_dda dda, t_tex *tex)
{
	if (dda.side == 0)
	{
		tex->wall_x = game->player_posy + dda.side_dist_x * dda.ray_dir.y;
		tex->wall_x -= floor(tex->wall_x);
	}
	else
	{
		tex->wall_x = game->player_posx + dda.side_dist_y * dda.ray_dir.x;
		tex->wall_x -= floor(tex->wall_x);
	}
	tex->tex_x = (int)(tex->wall_x * game->album[0].tex_width);
	if (dda.side == 0 && dda.ray_dir.x < 0)
		tex->tex_x = game->album[0].tex_width - (tex->tex_x + 1);
	if (dda.side == 1 && dda.ray_dir.y > 0)
		tex->tex_x = game->album[0].tex_width - (tex->tex_x + 1);
}

static int	assign_index(t_dda dda)
{
	if (dda.side == 0 && dda.ray_dir.x > 0)
		return (3);
	if (dda.side == 0 && dda.ray_dir.x < 0)
		return (2);
	if (dda.side == 1 && dda.ray_dir.y > 0)
		return (0);
	if (dda.side == 1 && dda.ray_dir.y < 0)
		return (1);
	return (-1);
}

//This line:
// tex->tex_pos = (dda.start - game->screen_height / 2 + dda.line_height / 2)
// 					* tex->step;
//is for the most part going to be zero, because
//start = game->screen_height / 2 - line_height / 2. So, in the
//equation where we have -game->screen_height / 2 + line_height / 2,
//that is basically the negative of start. Thus, for most of the
//the rays, tex_pos is usually start + (-1 * start) * step which 
//is equal to 0. However, when the player gets too close to the
//wall, start can get too large (out of screen bounds) so we end
//up manually changing start to 0! In that case, start is no
//longer equal to game->screen_height / 2 - line_height / 2. Thus,
//tex_pos instead ends up becoming -draw_start * step and not
//just zero because tex_pos = (0 - game->screen_height / 2 + 
//line_height / 2) * step) is the same as 
//tex_pos = (-draw_start) * step. This would give us the right
//tex_pos on the texture as per the actual line_height (which depends
//on side_dist_x or side_disty_y, the actual distance) because we do
//not want to start at the top of the texture in this case (when 
//we are too close to a wall). If it is still hard to understand,
//change tex_pos below equal to 0. If you do that, everything would
//look the same (because in all those cases, we actually are starting
//to draw from the top of the texture) EXCEPT for when you get to close
//to a wall. You'll then see the discrepancy along the ray slice that
//cover the whole screen and the other ray slices that taper down as
//the view gets "deeper" into the map.
//
//ALSO
//
//for this line to work:
// 	tex->tex_y = (int) tex->tex_pos & (game->album[0].tex_height - 1);
//tex dimensions have to be a power of 2 for the below
//masking/capping to work
void	texture_loop(t_game *game, t_tex *tex, t_dda dda, double x)
{
	int	color;
	int	offset;
	int	index;

	index = assign_index(dda);
	tex->step = ((double) game->album[index].tex_height / dda.line_height);
	tex->tex_pos = (dda.start - game->screen_height / 2 + 3
			* dda.line_height / 4) * tex->step;
	while (dda.start < dda.end)
	{
		tex->tex_y = (int) tex->tex_pos & (game->album[index].tex_height - 1);
		tex->tex_pos += tex->step;
		color = get_color(game, index, tex->tex_x, tex->tex_y);
		if (dda.side == 1)
			color = (color >> 1) & 8355711;
		offset = (game->screen_width * dda.start) + x;
		*(game->data.img.img_pixels_ptr + offset) = color;
		dda.start++;
	}
}

void	draw_ceiling_and_floor(t_game *game, t_dda dda, double x)
{
	draw_v_line(game, dda, x, game->floor_color);
	draw_v_line(game, dda, x, game->ceiling_color);
}
