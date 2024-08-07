/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:27 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/07 21:17:36 by rosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void print_pixel_data(t_wall *texture)
// {
//     int bpp = texture->bpp / 8; // Convert bits per pixel to bytes per pixel
// 	(void)bpp;
//     int width = texture->fixed_width;
//     int height = texture->fixed_height;
//     int *pixels = texture->img_pixels_ptr;

//     // Print pixel data for the first few rows and columns
//     printf("Printing first few pixel values:\n");
//     for (int y = 0; y < height && y < 5; y++) { // Limiting to the first 5 rows
//         for (int x = 0; x < width && x < 5; x++) { // Limiting to the first 5 columns
//             int index = (y * width + x); // Calculate the index in the pixel array

//             uint32_t color = pixels[index]; // Get the pixel value (assuming 32-bit color)

//             // Extract individual color components (assuming 8-bit per component and ARGB format)
//             uint8_t a = (color >> 24) & 0xFF; // Alpha component
//             uint8_t r = (color >> 16) & 0xFF; // Red component
//             uint8_t g = (color >> 8) & 0xFF;  // Green component
//             uint8_t b = color & 0xFF;         // Blue component

//             printf("Pixel (%d, %d): ARGB(%d, %d, %d, %d)\n", x, y, a, r, g, b);
//         }
//     }
// }

void	texture_parsing(t_data *data, t_wall *texture, char *line, int *flag)
{
	char	*store;

	if (texture->img)
		exit_texture(DUP, data, line);
	store = ft_strtrim(ft_strchr(line, ' ') + 1, " \n\t\v");
	data->paths[data->path_index++] = ft_strdup(store);
	// printf("stor : i: %s\n", store);
	// exit(0);
	texture->img = mlx_xpm_file_to_image(data->mlx.mlx_ptr, store,
			&(texture->fixed_width),
			&(texture->fixed_height));
	free(store);
	if (!texture->img)
		exit_texture(WRONG_FILE, data, line);
	texture->img_pixels_ptr = (int *)mlx_get_data_addr(texture->img,
			&(texture->bpp), &(texture->size_line),
			&(texture->endian));
	if (!texture->img_pixels_ptr)
		exit_texture("Failed to get texture data address", data, line);
// 	for (int i = 0; i < 4; i++) {
//     printf("Texture %d: First pixel color = %X\n", i, 
//            data->image.texture[i].img_pixels_ptr[0]);
// }
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
