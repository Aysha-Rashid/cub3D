/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytapano <ytapano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:56:53 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/21 20:57:36 by ytapano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_path(t_game *game, char *full, char *str, int index)
{
	int			i;

	i = 0;
	if (game->album[index].img != NULL)
		exit_err(game, full, "Duplicate texture identifier");
	while (str[i] && is_wspace(str[i]))
		i++;
	if (!str[i])
		exit_err(game, full, "A texture is missing a file name");
	game->album[index].img = mlx_xpm_file_to_image(game->data.mlx_ptr, str + i,
			&(game->album[index].tex_width), &(game->album[index].tex_height));
	if (game->album[index].img == NULL)
		exit_err(game, full, "Incorrect file path used for one or more"
			" textures");
	game->album[index].img_pixels_ptr = (int *)mlx_get_data_addr(
			game->album[index].img,
			&(game->album[index].bits_per_pixel),
			&(game->album[index].line_len),
			&(game->album[index].endian));
}

static int	get_tex_index(char *trimmed)
{
	int	index;

	index = 0;
	if (trimmed[0] == 'N')
		index = 0;
	else if (trimmed[0] == 'S')
		index = 1;
	else if (trimmed[0] == 'E')
		index = 2;
	else if (trimmed[0] == 'W')
		index = 3;
	return (index);
}

int	parse_textures(t_game *game, char *trimmed)
{
	if ((trimmed[0] == 'N' && trimmed[1] == 'O')
		|| (trimmed[0] == 'S' && trimmed[1] == 'O')
		|| (trimmed[0] == 'E' && trimmed[1] == 'A')
		|| (trimmed[0] == 'W' && trimmed[1] == 'E'))
	{
		get_path(game, trimmed, trimmed + 2, get_tex_index(trimmed));
		whitespace_checker(game, trimmed);
		return (1);
	}
	return (0);
}
