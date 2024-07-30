/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:59:49 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/29 17:17:48 by rosman           ###   ########.fr       */
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
	// int	i;

	// i = 0;
	// (void)data;
	// while (data->map && data->map[0])
	// 	free(data->map[i++]);
	// free(data->map);
	// i = 0;
	// while (data->paths[i])
	// {
	// 	printf("i : %d\n", i);
	// 	free(data->paths[i++]);
	// }
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
