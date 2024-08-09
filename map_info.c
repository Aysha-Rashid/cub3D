/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:56:44 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/09 16:03:46 by rosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	parse_mapline(t_data *data, char **map)
{
	int		i;
	int		j;
	int		count;

	i = -1;
	j = 0;
	count = 0;
	while (map[++i])
	{
		j = 0;
		if (map[i][0] == '\0')
		{
			while (map[i + j] != NULL)
			{
				if (map[i + j][0] != '\0')
					exit_error("Empty line in map", data);
				j++;
			}
		}
		count += check_valid_character(data, map[i]);
	}
	if (count != 1)
		exit_error("either no characters or more than 1", data);
}

static char	**x_map_mem_alloc(t_data *data, char **map)
{
	int		i;
	int		j;
	char	**buffer;
	int		max_len;

	i = 0;
	max_len = -2147483648;
	while (map[i])
		i++;
	buffer = (char **)malloc((i + 1) * (sizeof(char *)));
	data->map_height = i;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max_len)
			max_len = j;
		i++;
	}
	i = 0;
	while (map[i])
		buffer[i++] = (char *)malloc(max_len + 1);
	return (buffer[i] = NULL, data->map_width = max_len, buffer);
}

static void	fill_x_map(char **map, char **buffer, int max_len)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while ((map[i][j] >= 9 && map[i][j] <= 13) || map[i][j] == 32)
			buffer[i][j++] = 'X';
		while (map[i][j])
		{
			if (is_trailing_wspace(map[i], j))
				buffer[i][j] = 'X';
			else if ((map[i][j] >= 9 && map[i][j] <= 13) || map[i][j] == 32)
				buffer[i][j] = '0';
			else
				buffer[i][j] = map[i][j];
			j++;
		}
		while (j < max_len)
			buffer[i][j++] = 'X';
		buffer[i][j] = '\0';
		i++;
	}
}


char	**parse_map(t_data *data, char **map)
{
	char	**buffer;

	buffer = NULL;
	parse_mapline(data, map);
	buffer = x_map_mem_alloc(data, map);
	if (!buffer)
		(free_map(map), exit_error(MEMORY_ISSUE, data));
	fill_x_map(map, buffer, data->map_width);
	free_map(map);
	return (buffer);
}

void	put_player_dir(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'N')
	{
		data->view = (t_pix){0, -1};
		data->camera = (t_pix){0.66, 0};
	}
	else if (data->map[y][x] == 'S')
	{
		data->view = (t_pix){0, 1};
		data->camera = (t_pix){-0.66, 0};
	}
	else if (data->map[y][x] == 'E')
	{
		data->view = (t_pix){1, 0};
		data->camera = (t_pix){0, 0.66};
	}
	else if (data->map[y][x] == 'W')
	{
		data->view = (t_pix){-1, 0};
		data->camera = (t_pix){0, -0.66};
	}
}

void	put_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				put_player_dir(data, x, y);
				data->player_x = x + 0.5;
				data->player_y = y + 0.5;
			}
			if (data->map[y][x] == 'Y')
				place_object(&(data->object), y, x);
			x++;
		}
		y++;
	}
}

