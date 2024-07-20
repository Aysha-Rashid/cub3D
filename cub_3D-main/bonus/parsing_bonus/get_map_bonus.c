/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:00:28 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/22 16:31:59 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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

//if ft_strchr(map[i], \n) is used so that we keep the
//last line in the map if the user hadn't hit enter after
//the last line. So if the map[i] line where i represents the
//last line in the map ends with a '\0' instead of a '\n'
//(indicating that the user did not hit enter upon reaching
//the last line as mentioned earlier), then we keep the line
//as it is.
char	**get_map(t_game *game, int fd)
{
	char	**map;
	int		i;

	map = get_map_nl(fd);
	if (map == NULL)
		exit_err(game, NULL, "No map content found");
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
