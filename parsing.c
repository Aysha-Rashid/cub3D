/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:27 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/18 22:33:45 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texture_parsing(t_image *image, int *i, char *line, int *flag)
{
	int	fd;

	fd = 0;
	if (!(ft_strchr(line, ' ')))
		exit_error(WRONG_TEXTFILE);
	image->texture[*i] = ft_strdup(ft_strchr(line, ' ') + 1);
	*flag = 1;
	fd = open(image->texture[*i], O_RDONLY);
	if (fd == -1)
		exit_error(WRONG_TEXTFILE);
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
