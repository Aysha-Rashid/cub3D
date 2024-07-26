/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:27 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/26 21:02:11 by rosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texture_parsing(t_data *data, t_mlx	*texture, char *line, int *flag)
{
	(void)texture;
	char		*store;
	// static int	i = 0;

	// if (texture->img)
	// 	(free_texture(data, data->path_index - 1), exit_error(DUP, data));
	store = ft_strtrim(ft_strchr(line, ' ') + 1, " \n\t\v");
	// free(line);
	data->paths[data->path_index++] = ft_strdup(store);
	// texture->img = mlx_xpm_file_to_image(data->mlx.ptr, store,
	// 		&(data->mlx.fixed_width), &(data->mlx.fixed_height));
	free(store);
	// if (!texture->img)
	// 	(free_texture(data, data->path_index - 1), exit_error(WRONG_TEXTFILE, data));
	*flag = *flag + 1;
	// texture->img_pixels_ptr = (int *)mlx_get_data_addr(texture->img,
	// 		&(texture->bpp), &(texture->size_line),
	// 		&(texture->endian));
}

int	ceiling_floor(t_data *data, int *str, char *line, int *flag)
{
	char	*store;

	if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
	{
		*flag = *flag + 1;
		if (*str != -1)
			(free(line), close(data->file), free_texture(data, data->path_index - 1), exit_error(DUP, data));
		store = ft_strtrim(ft_strchr(line, ' ') + 1, " \n\t\v");
		// free(line);
		if (check_for_syntax(store))
		{
			free(line);
			free(store);
			close(data->file);
			free_texture(data, data->path_index - 1);
			exit_error(SYNTAX_ISSUE, data);
		}
		*str = set_color(store, data);
		if (data->image.ceiling && data->image.floor)
		{
			if (data->image.ceiling == data->image.floor)
			{
				free(line);
				free(store);
				close(data->file);
				free_texture(data, data->path_index - 1);
				exit_error("Same color for Ceiling and Floor", data);
			}
		}
		free(store);
		return (0);
	}
	*flag = *flag - 1;
	return (0);
}

void	handle_map_content(t_data *data, int fd)
{
	data->map = get_map(data, fd);
	parse_map(data, data->map);
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
	if (!line)
		(free(line), close(file), ft_putendl_fd("Error", 2), ft_putendl_fd(EMPTY_FILE, 2), exit(1));
	while (line && count != 6)
	{
		str = ft_strtrim(line, " \t\n\v");
		free(line);
		check_for_map_info(str, data, &count);
		free(str);
		line = get_next_line(file);
		if (!line)
			break ;
	}
	free(line);
	if (count != 6)
		(free_texture(data, data->path_index - 1), exit_error(TEXTURE_ERROR, data));
	check_texture(data);
	// handle_map_content(data, file);
	close(file);
}
