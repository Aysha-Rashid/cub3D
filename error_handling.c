/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:59:49 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/16 22:09:06 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "minilibx/mlx.h"

void	exit_error(char *error)
{
	ft_putendl_fd(error, 2);
	exit(0);
}

int	check_name(char *argv)
{
	char	*store;

	if (ft_strchr(argv, '.'))
		store = ft_strchr(argv, '.') + 1;
	else
		store = "wrong";
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