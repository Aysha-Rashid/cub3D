/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:07:29 by mawad             #+#    #+#             */
/*   Updated: 2024/05/25 18:40:31 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_2d_arr(char **map)
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

//Check later, naybe there is no need to even destroy mlx
//or game because by that point, we might not even have
//a map or initialized the mlx window yet.
void	exit_err(t_game *game, char *line, char *message)
{
	int	i;

	printf(RED"⚠️ Error ⚠️\n%s\n"OG, message);
	free(line);
	mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
	if (game->data.img.img_ptr != NULL)
		mlx_destroy_image(game->data.mlx_ptr, game->data.img.img_ptr);
	i = 0;
	while (i < 5)
	{
		if (game->album[i].img != NULL)
			mlx_destroy_image(game->data.mlx_ptr, game->album[i].img);
		i++;
	}
	destroy_2d_arr(game->map);
	close(game->fd);
	exit(1);
}

int	ft_destroy(t_game *game)
{
	int	i;

	mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
	if (game->data.img.img_ptr != NULL)
		mlx_destroy_image(game->data.mlx_ptr, game->data.img.img_ptr);
	i = 0;
	while (i < 5)
	{
		if (game->album[i].img != NULL)
			mlx_destroy_image(game->data.mlx_ptr, game->album[i].img);
		i++;
	}
	destroy_2d_arr(game->map);
	close(game->fd);
	exit(0);
	return (0);
}
