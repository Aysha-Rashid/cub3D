/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:26:01 by rosman            #+#    #+#             */
/*   Updated: 2024/07/30 14:37:43 by rosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_view(t_data *data)
{
	int	x;
	int	y;

	x = data->player_x;
	y = data->player_y;
	if (data->map[y][x] == 'N')
		data->player_angle = N_D0;
	else if (data->map[y][x] == 'E')
		data->player_angle = E_D90;
	else if (data->map[y][x] == 'S')
		data->player_angle = S_D180;
	else if (data->map[y][x] == 'W')
		data->player_angle = W_D270;
}
