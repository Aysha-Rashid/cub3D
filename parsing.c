/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:20:27 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/20 22:29:52 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
void	texture_parsing(t_image *image, char *path_texture, char *line, int *flag)
{
	int		fd;
	char	*store;

	store = "";
	fd = 0;
	image->fixed_height = 500;
	image->fixed_width = 1000;
	if (!(ft_strchr(line, ' ')))
		exit_error(WRONG_TEXTFILE);
	path_texture = ft_strdup(ft_strchr(line, ' ') + 1);
	printf("image %s\n", path_texture);
	*flag = *flag + 1;
	fd = open(path_texture, O_RDONLY);
	if (fd == -1)
		exit_error(WRONG_TEXTFILE);
	if (ft_strchr(path_texture, '.'))
		store = ft_strchr(path_texture, '.') + 1;
	if (ft_strcmp(store, "xpm"))
		exit_error(WRONG_TEX_EXTEN);
	close(fd);
}

void	ceiling_floor(t_image	*image, char *str, char *line, int *flag)
{
	(void)str;
	(void)flag;
	(void)image;
	if (!ft_strncmp(line, "C ", 2))
	{
		*flag = *flag + 1;
		return ;
	}
	if (!ft_strncmp(line, "F ", 2))
	{
		*flag = *flag + 1;
		return ;
	}
	*flag = *flag - 1;
	printf(" ceiling or floor %s\n", line);
}

int only_whitespace(char *str)
{
	int i = 0;
	while (str[i])
	{
		if ((str[i] > 9 && str[i] < 11) || str[i] == 32)
			return (1);
		i++;
	}
	return (0);
}

int	store_texture_and_parse(int fd, char *line, t_image *image)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (line && i != 6)// just for format testing (should change this based on what we decide on parsing)
	{
		if (only_whitespace(line))
			flag = flag - 1;
		if (!ft_strncmp(line, "SO ", 3))
			texture_parsing(image, image->south, line, &i);
		if (!ft_strncmp(line, "NO ", 3))
			texture_parsing(image, image->north, line, &i);
		if (!ft_strncmp(line, "WE ", 3))
			texture_parsing(image, image->west, line, &i);
		if (!ft_strncmp(line, "EA ", 3))
			texture_parsing(image, image->east, line, &i);
		if (!ft_strncmp(line, "C ", 2))
			ceiling_floor(image, image->east, line, &i);
		if (!ft_strncmp(line, "F ", 2))
			ceiling_floor(image, image->east, line, &i);
		printf("i = %d\n", i);
		free(line);
		line = get_next_line(fd);
		printf("line : %s\n", line);
		if (!line)
			break ;
		if (flag == 0)
			exit_error(TEXTURE_ERROR);
	}
	if (i != 6)
		(exit_error(TEXTURE_ERROR), free(line));
	// printf("what line? %s\n", line);
	return (flag);
}
void	read_map(int file, t_coor *coord)
{
	char	*line;
	int		length_of_line;

	line = get_next_line(file);
	length_of_line = 0;
	if (!line)
		exit_error(EMPTY_FILE);
	while (line)
	{
		store_texture_and_parse(file, line, &coord->image);
		// free(line);
		// line = get_next_line(file);
		printf("what line? %s\n", line);
		if (only_whitespace(line))
		{
			free(line);
			line = get_next_line(file);
		}
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
		coord->height++;
		(free(line), line = get_next_line(file));
	}
	free(line);
}
