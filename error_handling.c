/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:59:49 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/09 18:18:57 by ayal-ras         ###   ########.fr       */
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

int	ft_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
	free_texture(data, data->path_index - 1);
	free_map(data->map);
	exit(0);
	return (0);
}

void	exit_texture(char *message, t_data *data, char *line)
{
	(free(line), close(data->file),
		free_texture(data, data->path_index - 1),
		exit_error(message, data));
}

void	free_texture(t_data *data, int num)
{
	while (num >= 0)
		free(data->paths[num--]);
}
