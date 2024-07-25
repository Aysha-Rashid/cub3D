/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:56:44 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/25 22:30:34 by ayal-ras         ###   ########.fr       */
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
	data->coord.height = i;
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
	return (buffer[i] = NULL, data->coord.width = max_len, buffer);
}

int	is_trailing_wspace(char *str, int index) // keeps checking for space in the str from the j index untill the end of the string
// if anything other then space is found then its not towards the end.
{
	while (str[index])
	{
		if (str[index] != ' ')
			return (0);
		index++;
	}
	return (1);
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
	// i =0;
	// j = 0;
	// while(buffer[i])
	// {
	// 	j = 0;
	// 	while (buffer[i][j])
	// 	{
	// 		printf("%c", buffer[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
}

char	**parse_map(t_data *data, char **map)
{
	int		i;
	char	**buffer;

	buffer = NULL;
	i = 0;
	while (map[i])
	{
		if (ft_strchr(map[i], '\n'))
			map[i] = extract_line(map[i]);
		i++;
	}
	parse_mapline(data, map);
	buffer = x_map_mem_alloc(data, map);
	fill_x_map(map, buffer, data->coord.width);
	// map = buffer;
	// check for edge here
	return (buffer);
}

char	**get_map(t_data *data, int fd)
{
	char	*line;
	char	**map;
	int		y;

	line = get_next_line(fd);
	while (line && (line[0] == '\n' || line[1] == '\0'))
		(free(line), line = get_next_line(fd));
	if (!line)
		(free(line), exit_error(INVALID_MAP, data));
	map = (char **)malloc(sizeof(char *) * 10000);
	if (!map)
		(free(line), exit_error(INVALID_MAP, data));
	y = 0;
	while (line)
	{
		map[y] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!map[y])
			(free(line), free_map(map), exit_error(INVALID_MAP, data));
		ft_strlcpy(map[y++], line, ft_strlen(line) + 1);
		(free(line), line = get_next_line(fd));
	}
	(free(line), map[y] = NULL);
	return (map);
}
