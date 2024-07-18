/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:29:25 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/18 21:00:15 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// display different wall textures, that vary depending on which side the wall is facing
// (NORTH, SOUTH, EAST, WEST)
// set the floor and the ceiling colors to two different ones
// 
// keyboard (keyhooks)
// 1. left and right arrow must allow to look left and right
// 2. W, A, S, and D allows you to move the point of view.
// 3. ESC exits the window
// 4. red cross close the window
// 5. images of the minilibx is imp.

// first argument takes the scene description with .cub extension
// 6 possible characters: 0 for emp, 1 for wall, N, S, W, E for the player's starting point.
// 

#include "cub3D.h"
#include "minilibx/mlx.h"
#include <string.h>

int	skip_space_and_count(char *line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

// parsing the texture
void	texture_parsing(t_image *image, int *i, char *line, int *flag)
{
	int	fd;

	fd = 0;
	if (!(ft_strchr(line, ' ')))
		exit_error(WRONG_FILE);
	image->texture[*i] = ft_strdup(ft_strchr(line, ' ') + 1);
	*flag = 1;
	fd = open(image->texture[*i], O_RDONLY);
	if (fd == -1)
		exit_error(WRONG_FILE);
	close(fd);
}

int	store_texture_and_parse(int fd, char *line, t_image *image)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (i < 4)
	{
		flag = 0;
		if (!ft_strncmp(line, "SO", 2))
			texture_parsing(image, &i, line, &flag);
		if (!ft_strncmp(line, "NO", 2))
			texture_parsing(image, &i, line, &flag);
		if (!ft_strncmp(line, "WE", 2))
			texture_parsing(image, &i, line, &flag);
		if (!ft_strncmp(line, "EA", 2))
			texture_parsing(image, &i, line, &flag);
		image->fixed_height = 500;
		image->fixed_width = 1000;
		(i++, free(line));
		line = get_next_line(fd);
		if (!line)
			break ;
		if (flag == 0)
			exit_error(TEXTURE_ERROR);
	}
	return (free(line), flag);
}

void	read_map(int file, t_coor *coord)
{
	char	*line;
	int		length_of_line;

	line = get_next_line(file);
	if (!line)
		exit_error(EMPTY_FILE);
	length_of_line = 0;
	if (!store_texture_and_parse(file, line, &coord->image))
		exit_error(TEXTURE_ERROR);
	line = get_next_line(file);
	while (line)
	{
		// check and store the texture for N, W, E and S.
		// check if the path to the texture of them are valid
		if (ft_strchr(line, ' '))
			coord->width = skip_space_and_count(line);
		else
			coord->width = ft_strlen(line);
		if (length_of_line)
		{
			if (length_of_line != coord->width)
				exit_error(INVALID_MAP);
		}
		length_of_line = coord->width;
		coord->height = coord->height + 1;
		free(line);
		line = get_next_line(file);
	}
	free(line);
}

void	init_data(t_data *data, char *file_name)
{
	data->file = open(file_name, O_RDONLY);
	if (data->file == -1)
		exit_error(WRONG_FILE);
	data->coord.width = 0;
	data->coord.height = 0;
	data->coord.x = 0;
	data->coord.y = 0;
	read_map(data->file, &data->coord);
	close(data->file);
}

void	init_mlx(t_mlx mlx)
{
	mlx.bpp = 0;
	mlx.endian = 0;
	mlx.img = 0;
	mlx.ptr = 0;
	mlx.size_line = 0;
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_data	data;

	if (argc != 2)
		exit_error(INVALID);
	if (argc > 1)
	{
		if (check_name(argv[1]))
			exit_error(WRONG_EXTEN);
		init_data(&data, argv[1]);
		mlx.ptr = mlx_init();
		mlx.win = mlx_new_window(mlx.ptr, 1000, 1000, "cub3d");
		init_mlx(mlx);
		mlx_key_hook(mlx.win, esc_key, &mlx);
		mlx_loop(mlx.ptr);
	}
}


// map are not parsing with spaces rather they are parse by each digit (remove spaces in between each other).
// eg : if map is = 1 1 1 1 (this is not valid) so is 1111 (this is also alright) so is 1211 (this is also correct)
