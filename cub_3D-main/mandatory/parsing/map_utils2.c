/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytapano <ytapano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:57:16 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/21 20:57:19 by ytapano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	**x_map_mem_alloc(t_game *game, char **map)
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
	game->map_ind_height = i;
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
	return (buffer[i] = NULL, game->map_ind_width = max_len, buffer);
}

static void	fill_x_map(char **map, char **buffer, int max_len)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (is_wspace(map[i][j]))
			buffer[i][j++] = 'X';
		while (map[i][j])
		{
			if (is_trailing_wspace(map[i], j))
				buffer[i][j] = 'X';
			else if (is_wspace(map[i][j]))
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

//Fill preceeding and trailing spaces with X's
//Fill intermediate spaces with 0's
char	**ft_realloc_x(t_game *game, char **map)
{
	char	**buffer;
	int		max_len;

	buffer = x_map_mem_alloc(game, map);
	max_len = game->map_ind_width;
	fill_x_map(map, buffer, max_len);
	destroy_2d_arr(map);
	return (buffer);
}
