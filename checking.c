/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:33:47 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/03 19:15:45 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_valid_character(t_data *data, char *map)
{
	int		i;
	int		count;
	char	*set;

	count = 0;
	set = "NSWE10 ";
	i = 0;
	while (map[i])
	{
		if (!ft_strchr(set, map[i]))
			exit_error("invalid character in map", data);
		if (map[i] == 'N' || map[i] == 'S'
			|| map[i] == 'W' || map[i] == 'E')
		{
			count++;
			i++;
		}
		i++;
	}
	return (count);
}

void	check_boundary(t_data *data, char **test_map, int x, int y)
{
	t_pos	four_dir[4];
	t_pos	pos;
	int		counter;
	int		i;

	pos = (t_pos){x, y};
	if (pos.x == 0 || pos.x == data->map_width - 1
		|| pos.y == 0 || pos.y == data->map_height - 1)
	{
		free_map(test_map);
		exit_error("Map not surrouned by walls", data);
	}
	i = 0;
	counter = search_dir(data, pos, four_dir);
	while (i < counter)
	{
		x = four_dir[i].x;
		y = four_dir[i].y;
		if (data->map[y][x] == 'X')
		{
			free_map(test_map);
			exit_error("Map not surrouned by walls", data);
		}
		i++;
	}
}

void	checking_after_dfs(t_data *data, char **test_map)
{
	int	i;
	int	j;

	i = 0;
	while (test_map[i])
	{
		j = 0;
		while (test_map[i][j])
		{
			if (test_map[i][j] == 'V')
				check_boundary(data, test_map, j, i);
			else if (test_map[i][j] == 'A'
				&& !(data->map[i][j] == '1' || data->map[i][j] == 'X'))
			{
				free_map(test_map);
				exit_error("Only spaces beyond map walls and "
					"no spaces/zeroes allowed within perimeter wall", data);
			}
			j++;
		}
		i++;
	}
}

void	check_texture(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = i + 1;
		while (j < 4)
		{
			if (ft_strcmp(data->paths[i], data->paths[j]) == 0)
			{
				close(data->file);
				free_texture(data, 3);
				exit_error("One of the texture is same!", data);
			}
			j++;
		}
		i++;
	}
}

int	check_name(char *argv)
{
	char	*store;

	store = "";
	if (ft_strchr(argv, '.'))
		store = ft_strchr(argv, '.') + 1;
	if (!ft_strcmp(store, "cub"))
		return (0);
	return (1);
}
