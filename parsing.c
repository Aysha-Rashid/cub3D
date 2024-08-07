/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:27 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/06 19:29:21 by rosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texture_parsing(t_data *data, t_wall *texture, char *line, int *flag)
{
	char		*store;

	if (texture->img)
		exit_texture(DUP, data, line);
	store = ft_strtrim(ft_strchr(line, ' ') + 1, " \n\t\v");
	data->paths[data->path_index++] = ft_strdup(store);
	// printf("stor : i: %s\n", store);
	// exit(0);
	texture->img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, store,
			&(texture->fixed_width),
			&(texture->fixed_height));
	// printf("fixed_width %d\n : ", data->image.texture->fixed_width);
	// printf("fixed_height %d\n : ", data->image.texture->fixed_height);
	free(store);
	if (!texture->img)
		exit_texture(WRONG_FILE, data, line);
	texture->img_pixels_ptr = (int *)mlx_get_data_addr(texture->img,
			&(texture->bpp), &(texture->size_line),
			&(texture->endian));
	// printf("img_pixel_ptr : %d\n", *texture->img_pixels_ptr);
	
	// exit(0);
	*flag = *flag + 1;
}

int	ceiling_floor(t_data *data, int *str, char *line, int *flag)
{
	char	*store;

	store = NULL;
	if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
	{
		if (*str != -1)
			exit_texture(DUP, data, line);
		store = ft_strtrim(ft_strchr(line, ' ') + 1, " \n\t\v");
		if (check_for_syntax(store))
			(free(store), exit_texture(SYNTAX_ISSUE, data, line));
		*str = set_color(store, data);
		if (data->image.ceiling && data->image.floor)
		{
			if (data->image.ceiling == data->image.floor)
				(free(store), exit_texture(COLOR_ISSUE,
						data, line));
		}
		*flag = *flag + 1;
		free(store);
		return (0);
	}
	return (0);
}

void	handle_map_content(t_data *data, int fd)
{
	char	**test_map;

	data->map = get_map(data, fd);
	data->map = parse_map(data, data->map);
	close(data->file);
	if (data->map_height < 3 || data->map_width < 3)
		(exit_error("Map is too small!", data));
	put_player(data);
	test_map = put_test_map(data->map);
	dfs(data, test_map, (int) data->player_x, (int) data->player_y);
	checking_after_dfs(data, test_map);
	free_map(test_map);
}

void	check_for_map_info(char *str, t_data *data, int *count)
{
	if (!ft_strncmp(str, "SO ", 3))
		texture_parsing(data, &data->image.texture[SO], str, count);
	else if (!ft_strncmp(str, "NO ", 3))
		texture_parsing(data, &data->image.texture[NO], str, count);
	else if (!ft_strncmp(str, "WE ", 3))
		texture_parsing(data, &data->image.texture[WE], str, count);
	else if (!ft_strncmp(str, "EA ", 3))
		texture_parsing(data, &data->image.texture[EA], str, count);
	else if (!ft_strncmp(str, "C ", 2))
		ceiling_floor(data, &data->image.ceiling, str, count);
	else if (!ft_strncmp(str, "F ", 2))
		ceiling_floor(data, &data->image.floor, str, count);
}

void	read_map(int file, t_data *data)
{
	char	*line;
	char	*str;
	int		count;

	count = 0;
	line = get_next_line(file);
	while (line && count != 6)
	{
		str = ft_strtrim(line, " \t\n\v");
		free(line);
		check_for_map_info(str, data, &count);
		free(str);
		if (count != 6)
			line = get_next_line(file);
	}
	if (count != 6)
		(free_texture(data, data->path_index - 1),
			close(data->file), exit_error(TEXTURE_ERROR, data));
	check_texture(data);
	handle_map_content(data, file);
	close(file);
}
