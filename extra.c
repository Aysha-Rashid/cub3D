/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:45:32 by rosman            #+#    #+#             */
/*   Updated: 2024/08/02 13:44:50 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(char **map) // just for testing, will remove it later
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

char	**put_test_map(char **map)
{
	int		i;
	int		j;
	char	**temp_map;

	i = 0;
	while (map[i])
		i++;
	temp_map = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (map[i])
	{
		j = 0;
		temp_map[i] = (char *)malloc(ft_strlen(map[i]) + 1);
		while (map[i][j])
			temp_map[i][j++] = 'A';
		temp_map[i][j] = '\0';
		i++;
	}
	temp_map[i] = NULL;
	return (temp_map);
}

int	search_corners(t_data *data, t_pos pos, t_pos *four_dir)
{
	if (pos.x == 0 && pos.y == 0)
		return (four_dir[0] = (t_pos){pos.x, pos.y + 1},
				four_dir[1] = (t_pos){pos.x + 1, pos.y},
				2);
	else if (pos.x == data->coord.width - 1 && pos.y == 0)
		return (four_dir[0] = (t_pos){pos.x, pos.y + 1},
				four_dir[1] = (t_pos){pos.x - 1, pos.y},
				2);
	else if (pos.x == 0 && pos.y == data->coord.height - 1)
		return (four_dir[0] = (t_pos){pos.x, pos.y - 1},
				four_dir[1] = (t_pos){pos.x + 1, pos.y},
				2);
	else if (pos.x == data->coord.width - 1
		&& pos.y == data->coord.height - 1)
		return (four_dir[0] = (t_pos){pos.x, pos.y - 1},
				four_dir[1] = (t_pos){pos.x - 1, pos.y},
				2);
	else if (pos.y == 0)
		return (four_dir[0] = (t_pos){pos.x, pos.y + 1},
				four_dir[1] = (t_pos){pos.x - 1, pos.y},
				four_dir[2] = (t_pos){pos.x + 1, pos.y},
				3);
	return (-1);
}

int	search_mid(t_data *data, t_pos pos, t_pos *four_dir)
{
	if (pos.y == data->coord.height - 1)
		return (four_dir[0] = (t_pos){pos.x, pos.y - 1},
				four_dir[1] = (t_pos){pos.x - 1, pos.y},
				four_dir[2] = (t_pos){pos.x + 1, pos.y},
				3);
	else if (pos.x == 0)
		return (four_dir[0] = (t_pos){pos.x, pos.y - 1},
				four_dir[1] = (t_pos){pos.x, pos.y + 1},
				four_dir[2] = (t_pos){pos.x + 1, pos.y},
				3);
	else if (pos.x == data->coord.width - 1)
		return (four_dir[0] = (t_pos){pos.x, pos.y - 1},
				four_dir[1] = (t_pos){pos.x, pos.y + 1},
				four_dir[2] = (t_pos){pos.x - 1, pos.y},
				3);
	else
		return (four_dir[0] = (t_pos){pos.x, pos.y - 1},
				four_dir[1] = (t_pos){pos.x, pos.y + 1},
				four_dir[2] = (t_pos){pos.x - 1, pos.y},
				four_dir[3] = (t_pos){pos.x + 1, pos.y},
				4);
	return (-1);
}

int	search_dir(t_data *data, t_pos pos, t_pos *four_dir)
{
	int	dir_count;

	dir_count = search_corners(data, pos, four_dir);
	if (dir_count == -1)
		dir_count = search_mid(data, pos, four_dir);
	return (dir_count);
}

void	dfs(t_data *data, char **test_map, int x, int y)
{
	t_pos	four_dir[4];
	t_pos	pos;
	int		counter;
	int		i;

	test_map[y][x] = 'V';
	i = 0;
	pos = (t_pos){x, y};
	counter = search_dir(data, pos, four_dir);
	while (i < counter)
	{
		x = four_dir[i].x;
		y = four_dir[i].y;
		if (!(data->map[y][x] == '1' || data->map[y][x] == 'X')
				&& test_map[y][x] == 'A')
			dfs(data, test_map, x, y);
		i++;
	}
}
