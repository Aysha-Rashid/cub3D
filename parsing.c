/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:27 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/22 22:42:55 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texture_parsing(t_data *data, t_mlx	*path_texture, char *line, int *flag)
{
	char	*store;

	if (path_texture->img)
		exit_error(DUP, data);
	store = ft_strtrim(ft_strchr(line, ' ') + 1, " \n\t\v");
	path_texture->img = mlx_xpm_file_to_image(data->mlx.ptr, store,
			&(data->mlx.fixed_width), &(data->mlx.fixed_height));
	free(store);
	if (!path_texture->img)
		exit_error(WRONG_TEXTFILE, data);
	*flag = *flag + 1;
	path_texture->img_pixels_ptr = (int *)mlx_get_data_addr(path_texture->img,
			&(path_texture->bpp), &(path_texture->size_line),
			&(path_texture->endian));
}

int	ceiling_floor(t_data *data, int *str, char *line, int *flag)
{
	char	*store;

	if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
	{
		*flag = *flag + 1;
		if (*str != -1)
			exit_error(DUP, data);
		store = ft_strtrim(ft_strchr(line, ' ') + 1, " \n\t\v");
		if (check_for_syntax(store))
			exit_error(SYNTAX_ISSUE, data);
		*str = set_color(store);
		free(store);
		return (0);
	}
	*flag = *flag - 1;
	return (0);
}

void	handle_map_content(t_data *data, int fd)
{
	char	*line;
	int		length_of_line;

	length_of_line = 0;
	line = get_next_line(fd);
	while (line)
	{
		line = ft_strtrim(line, " \n\t\v");
		printf("what line? %s\n", line);
		if (ft_strchr(line, ' '))
			data->coord.width = skip_space_and_count(line);
		else
			data->coord.width = ft_strlen(line);
		if (length_of_line)
		{
			if (length_of_line != data->coord.width)
				exit_error(INVALID_MAP, data);
		}
		length_of_line = data->coord.width;
		data->coord.height++;
		(free(line), line = get_next_line(fd));
	}
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
		(ft_putendl_fd("Error", 2), ft_putendl_fd(EMPTY_FILE, 2), exit(1));
	while (line && count != 6)
	{
		str = ft_strtrim(line, " \t\n\v");
		free(line);
		check_for_map_info(str, data, &count);
		line = get_next_line(file);
		if (!line)
			break ;
	}
	free(line);
	if (count != 6)
		exit_error(TEXTURE_ERROR, data);
	check_texture(data);
	// handle_map_content(data, file);
}
