/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:19:32 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/09 18:09:40 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*buffer;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	buffer = malloc(sizeof(*buffer) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!buffer)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		buffer[i] = s1[i];
		i++;
	}
	free(s1);
	j = 0;
	while (s2[j])
		buffer[i++] = s2[j++];
	buffer[i] = '\0';
	return (buffer);
}

int	is_trailing_wspace(char *str, int index)
{
	while (str[index])
	{
		if (str[index] != ' ')
			return (0);
		index++;
	}
	return (1);
}

void	flush(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->screen_height)
	{
		x = 0;
		while (x < data->screen_width)
		{
			my_pixel_put(data, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	delta_dist(t_dda *dda)
{
	if (dda->ray_dir.x == 0.00)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir.x);
	if (dda->ray_dir.y == 0.00)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir.y);
}

void	side_dist(t_pix *pos, t_dda *dda)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (pos->x - dda->map.x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = ((1 - (pos->x - dda->map.x)) * dda->delta_dist_x);
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (pos->y - dda->map.y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (1 - (pos->y - dda->map.y)) * dda->delta_dist_y;
	}
}
