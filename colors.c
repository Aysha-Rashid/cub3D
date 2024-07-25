/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:40:50 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/24 13:34:35 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_for_syntax(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == ',')
		{
			count++;
			i++;
		}
		else if (!ft_isdigit(str[i]))
			return (1);
		else
			i++;
	}
	if (count == 0 || count > 2)
		return (1);
	return (0);
}

static int	convert_rgb(long long int *rgb)
{
	int	color;
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] > 255 || rgb[i] < 0)
		{
			printf("r, g, b values outside 0-255 range\n");
			exit(1);
		}
		i++;
	}
	color = rgb[0] * (pow(256, 2)) + (rgb[1] * 256) + rgb[2]; // combined decimal values of rgb
	printf("colors : %d\n", color);
	return (color);
}

int	set_color(char *str)
{
	int				i;
	int				j;
	int				k;
	long long int	rgb[3];
	int				color;

	i = 0;
	k = 0;
	j = 0;
	color = 0;
	while (str[i])
	{
		j = 0;
		while (ft_isdigit(str[i + j]))
			j++;
		if (j != 0)
		{
			rgb[k++] = ft_atoi(str + i);
			i = i + j;
		}
		else
			i++;
	}
	color = convert_rgb(rgb);
	return (color);
}
