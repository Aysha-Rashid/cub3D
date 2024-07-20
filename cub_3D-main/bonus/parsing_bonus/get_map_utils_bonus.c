/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytapano <ytapano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:00:24 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/21 21:00:34 by ytapano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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

t_bool	valid_line(char *line)
{
	char	*set;
	int		i;

	i = 0;
	set = "01NSEW ";
	while (line[i])
	{
		if (!ft_strchr(set, line[i]))
		{
			printf("char that fucked us is -%c-\n", line[i]);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	parse_map_lines(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		if (map[i][0] == '\0')
		{
			while (map[i + j] != NULL)
			{
				if (map[i + j][0] != '\0')
					exit_err(game, NULL, "Empty line not allowed"
						" in map content");
				j++;
			}
		}
		if (valid_line(map[i]) == FALSE)
			exit_err(game, NULL, "Invalid map line");
		i++;
	}
}

// void	parse_map_lines(t_game *game, char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i])
// 	{
// 		if (map[i][0] == '\0')
// 			exit_err(game, NULL, "Empty line not allowed"
// 				" in map content");
// 		if (valid_line(map[i]) == FALSE)
// 			exit_err(game, NULL, "Invalid map line");
// 		i++;
// 	}
// }
