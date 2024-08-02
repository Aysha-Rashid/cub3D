/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:59:49 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/02 13:43:50 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	if (map[0] == NULL)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	exit_error(char *error, t_data *data)
{
	free_map(data->map);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error, 2);
	exit(1);
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

int	esc_key(int key, t_mlx *matrix)
{
	if (key == 53)
	{
		mlx_destroy_window(matrix->ptr, matrix->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	exit_texture(char *message, t_data *data, char *line)
{
	(free(line), close(data->file),
		free_texture(data, data->path_index - 1),
		exit_error(message, data));
}
