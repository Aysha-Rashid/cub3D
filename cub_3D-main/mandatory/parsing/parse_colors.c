/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:57:03 by ytapano           #+#    #+#             */
/*   Updated: 2024/07/20 21:53:23 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	convert_rgb(t_game *game, char *line, long long int *rgb)
{
	int	color;
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] > 255 || rgb[i] < 0)
			exit_err(game, line,
				"r, g, b values outside of 0-255 range");
		i++;
	}
	color = rgb[0] * (pow(256, 2)) + (rgb[1] * 256) + rgb[2];
	return (color);
}

//This line:
//		if (str[i] == ',' && rgb[0] != -1)
// 			i++;
//was added to ensure that a ',' shall not be accepted the first
//value (the r (red) value), only after the first, or second value.
//So something like C ,242, 30, 0 is handled by that line.
static int	set_color(t_game *game, char *full, char *str)
{
	int				i;
	int				j;
	int				k;
	long long int	rgb[3];
	int				color;

	i = 0;
	k = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (ft_isdigit(str[i + j]))
			j++;
		if (j != 0)
		{
			rgb[k++] = ft_atol(str + i);
			printf("str + i : %s\n", str + i);
			i = i + j;
		}
		else
			i++;
	}
	color = convert_rgb(game, full, rgb);
	return (color);
}

int	parse_colors(t_game *game, char *trimmed)
{
	if (trimmed[0] == 'C' && is_wspace(trimmed[1]))
	{
		whitespace_checker(game, trimmed);
		check_rgb_syntax(game, trimmed, trimmed + 1);
		if (game->ceiling_color != -1)
			exit_err(game, trimmed, "Duplicate color identifier");
		game->ceiling_color = set_color(game, trimmed, trimmed + 1);
		return (1);
	}
	else if (trimmed[0] == 'F' && is_wspace(trimmed[1]))
	{
		whitespace_checker(game, trimmed);
		check_rgb_syntax(game, trimmed, trimmed + 1);
		if (game->floor_color != -1)
			exit_err(game, trimmed, "Duplicate color identifier");
		game->floor_color = set_color(game, trimmed, trimmed + 1);
		return (1);
	}
	else if (trimmed[0] == '\n' || trimmed[0] == '\0')
		return (0);
	else
		return (-1);
}
