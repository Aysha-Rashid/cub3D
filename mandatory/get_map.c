/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:03:31 by rosman            #+#    #+#             */
/*   Updated: 2024/08/02 13:42:52 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_map_alloc_clean(char **map, char *line, int y)
{
	int	i;

	i = 0;
	free(line);
	if (y != -1)
	{
		while (i < y)
			free(map[i++]);
	}
	free(map);
	printf("Invalid map line\n");
	exit(1);
}

static char	*first_row(int fd, char **map, int *y)
{
	char	*row;

	if (map == NULL)
		return (NULL);
	row = get_next_line(fd);
	if (!row)
		return (free(row), NULL);
	while (row[0] == '\n' && row[1] == '\0')
	{
		free(row);
		row = get_next_line(fd);
		if (!row)
			return (NULL);
	}
	*y = 0;
	map[*y] = (char *)malloc(sizeof(char) * (ft_strlen(row) + 1));
	if (!map[*y])
		return (free(map), NULL);
	ft_strlcpy(map[(*y)++], row, ft_strlen(row) + 1);
	return (row);
}

static char	**get_map_nl(int fd)
{
	char	**map;
	char	*row;
	int		y;

	y = 0;
	map = (char **)malloc(sizeof(char *) * (9999));
	row = first_row(fd, map, &y);
	if (!row)
		return (free(map), NULL);
	free(row);
	while (row)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		map[y] = (char *)malloc(sizeof(char) * (ft_strlen(row) + 1));
		if (!map[y])
			return (ft_map_alloc_clean(map, row, y), NULL);
		ft_strlcpy(map[y++], row, ft_strlen(row) + 1);
		free(row);
	}
	return (map[y] = NULL, map);
}

static char	*extract_nl(char *line)
{
	int		i;
	char	*buffer;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	buffer = malloc(sizeof(*buffer) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n')
	{
		buffer[i] = line[i];
		i++;
	}
	buffer[i] = '\0';
	free(line);
	return (buffer);
}

char	**get_map(t_data *data, int fd)
{
	char	**map;
	int		i;

	map = get_map_nl(fd);
	if (map == NULL)
		(close(fd), exit_error(INVALID_MAP, data));
	i = 0;
	while (map[i])
	{
		if (ft_strchr(map[i], '\n'))
			map[i] = extract_nl(map[i]);
		i++;
	}
	i = 0;
	return (map);
}
