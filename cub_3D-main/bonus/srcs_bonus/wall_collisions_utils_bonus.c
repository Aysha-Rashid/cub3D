/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collisions_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:48:04 by mawad             #+#    #+#             */
/*   Updated: 2024/05/18 22:09:00 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	set_angle(t_vector *vec, double angle)
{
	double	vec_x_save;

	vec_x_save = vec->x;
	vec->x = cos(angle) * vec->x - sin(angle) * vec->y;
	vec->y = sin(angle) * vec_x_save + cos(angle) * vec->y;
}

int	mini_cast(t_game *game, int key)
{
	t_dda		dda;
	t_vector	pos;

	pos = (t_vector){game->player_posx, game->player_posy};
	dda.side = 0;
	dda.hit = FALSE;
	dda.ray_dir.x = game->dir.x;
	dda.ray_dir.y = game->dir.y;
	if (key == D_KEY)
		set_angle(&(dda.ray_dir), 1.5708);
	else if (key == A_KEY)
		set_angle(&(dda.ray_dir), -1.5708);
	else if (key == S_KEY)
		set_angle(&(dda.ray_dir), 3.14159);
	dda.map.x = (int) game->player_posx;
	dda.map.y = (int) game->player_posy;
	set_up_delta_dist(&dda);
	set_up_side_dist(&pos, &dda);
	dda_loop(game, &dda);
	return (dda.side);
}

t_bool	check_right_of_vertical(t_game *game)
{
	t_vector	vertical;
	double		cross_product;

	vertical.x = 0;
	if (game->dir.y >= 0)
		vertical.y = 1;
	else
		vertical.y = -1;
	cross_product = game->dir.x * vertical.y + game->dir.y * vertical.x;
	if (cross_product >= 0)
		return (TRUE);
	return (FALSE);
}

t_bool	check_right_of_horizontal(t_game *game)
{
	t_vector	horizontal;
	double		cross_product;

	if (game->dir.x >= 0)
		horizontal.x = 1;
	else
		horizontal.x = -1;
	horizontal.y = 0;
	cross_product = game->dir.x * horizontal.y + game->dir.y * horizontal.x;
	if (cross_product >= 0)
		return (TRUE);
	return (FALSE);
}

t_bool	check_valid_slide(t_game *game, t_vector target, int side)
{
	if (side == 0)
	{
		if (game->map[(int) target.y][(int) target.x] != '1'
			&& target.y < game->map_ind_height - 1
			&& target.y >= 1)
		{
			game->player_posx = target.x;
			game->player_posy = target.y;
		}
		return (TRUE);
	}
	else if (side == 1)
	{
		if (game->map[(int) target.y][(int) target.x] != '1'
			&& target.x < game->map_ind_width - 1
			&& target.y >= 1)
		{
			game->player_posx = target.x;
			game->player_posy = target.y;
		}
		return (TRUE);
	}
	return (FALSE);
}
