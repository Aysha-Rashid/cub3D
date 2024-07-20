/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:57:47 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/24 23:55:11 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "..//cub3d.h"

char	**mark_map_spawn(t_game *game, char **map)
{
	int		i;
	int		j;
	char	**buffer;

	(void) game;
	i = 0;
	while (map[i])
		i++;
	buffer = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (map[i])
	{
		j = 0;
		buffer[i] = (char *)malloc((ft_strlen(map[i]) + 1));
		while (map[i][j])
			buffer[i][j++] = 'F';
		buffer[i][j] = '\0';
		i++;
	}
	buffer[i] = NULL;
	return (buffer);
}

void	dfs(t_game *game, char **mark_map, int x, int y)
{
	t_index	neighbors[4];
	int		k;
	int		neighbor_count;
	t_index	pos;

	mark_map[y][x] = 'T';
	k = 0;
	pos = (t_index){x, y};
	neighbor_count = find_neighbors(game, pos, neighbors);
	while (k < neighbor_count)
	{
		x = neighbors[k].x;
		y = neighbors[k].y;
		if (!(game->map[y][x] == '1' || game->map[y][x] == 'X')
				&& mark_map[y][x] == 'F')
			dfs(game, mark_map, x, y);
		k++;
	}
}

void	check_boundary(t_game *game, char **marked_map, int x, int y)
{
	t_index	neighbors[4];
	int		neighbor_count;
	int		k;
	t_index	pos;

	pos = (t_index){x, y};
	if (pos.x == 0 || pos.x == game->map_ind_width - 1
		|| pos.y == 0 || pos.y == game->map_ind_height - 1)
	{
		destroy_2d_arr(marked_map);
		exit_err(game, NULL, "Map not surrouned by walls");
	}
	k = 0;
	neighbor_count = find_neighbors(game, pos, neighbors);
	while (k < neighbor_count)
	{
		x = neighbors[k].x;
		y = neighbors[k].y;
		if (game->map[y][x] == 'X')
		{
			destroy_2d_arr(marked_map);
			exit_err(game, NULL, "Map not surrouned by walls");
		}
		k++;
	}
}

void	parse_marked_map(t_game *game, char **marked_map)
{
	int	i;
	int	j;

	i = 0;
	while (marked_map[i])
	{
		j = 0;
		while (marked_map[i][j])
		{
			if (marked_map[i][j] == 'T')
				check_boundary(game, marked_map, j, i);
			else if (marked_map[i][j] == 'F'
				&& !(game->map[i][j] == '1' || game->map[i][j] == 'X'))
			{
				destroy_2d_arr(marked_map);
				printf("Issue: map[%d][%d] = %d\n", i, j, game->map[i][j]);
				exit_err(game, NULL, "Only spaces beyond map walls and "
					"no spaces/zeroes allowed within perimeter wall");
			}
			j++;
		}
		i++;
	}
}
