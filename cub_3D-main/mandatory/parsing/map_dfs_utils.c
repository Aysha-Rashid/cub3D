/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dfs_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytapano <ytapano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:57:53 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/21 20:57:55 by ytapano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//Nieghbors arranged in: up, down, left, right
static int	find_neighbors1(t_game *game, t_index pos, t_index *neighbors)
{
	if (pos.x == 0 && pos.y == 0)
		return (neighbors[0] = (t_index){pos.x, pos.y + 1},
				neighbors[1] = (t_index){pos.x + 1, pos.y},
				2);
	else if (pos.x == game->map_ind_width - 1 && pos.y == 0)
		return (neighbors[0] = (t_index){pos.x, pos.y + 1},
				neighbors[1] = (t_index){pos.x - 1, pos.y},
				2);
	else if (pos.x == 0 && pos.y == game->map_ind_height - 1)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x + 1, pos.y},
				2);
	else if (pos.x == game->map_ind_width - 1
		&& pos.y == game->map_ind_height - 1)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x - 1, pos.y},
				2);
	else if (pos.y == 0)
		return (neighbors[0] = (t_index){pos.x, pos.y + 1},
				neighbors[1] = (t_index){pos.x - 1, pos.y},
				neighbors[2] = (t_index){pos.x + 1, pos.y},
				3);
	return (-1);
}

//Nieghbors arranged in: up, down, left, right
static int	find_neighbors2(t_game *game, t_index pos, t_index *neighbors)
{
	if (pos.y == game->map_ind_height - 1)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x - 1, pos.y},
				neighbors[2] = (t_index){pos.x + 1, pos.y},
				3);
	else if (pos.x == 0)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x, pos.y + 1},
				neighbors[2] = (t_index){pos.x + 1, pos.y},
				3);
	else if (pos.x == game->map_ind_width - 1)
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x, pos.y + 1},
				neighbors[2] = (t_index){pos.x - 1, pos.y},
				3);
	else
		return (neighbors[0] = (t_index){pos.x, pos.y - 1},
				neighbors[1] = (t_index){pos.x, pos.y + 1},
				neighbors[2] = (t_index){pos.x - 1, pos.y},
				neighbors[3] = (t_index){pos.x + 1, pos.y},
				4);
	return (-1);
}

//Nieghbors arranged in: up, down, left, right
int	find_neighbors(t_game *game, t_index pos, t_index *neighbors)
{
	int	neighbor_count;

	neighbor_count = find_neighbors1(game, pos, neighbors);
	if (neighbor_count == -1)
		neighbor_count = find_neighbors2(game, pos, neighbors);
	return (neighbor_count);
}
