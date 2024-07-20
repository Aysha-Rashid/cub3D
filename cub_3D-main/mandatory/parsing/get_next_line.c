/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytapano <ytapano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:58:24 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/21 20:58:27 by ytapano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	nb_check(int nb_read, char *line, char *buffer)
{
	if (nb_read == -1)
	{
		if (line)
			free(line);
		return (free(buffer), 0);
	}
	if (nb_read == 0)
	{
		return (free(buffer), 1);
	}
	return (2);
}

char	*get_next_line(int fd)
{
	int		nb_read;
	char	*buffer;
	char	*line;

	nb_read = -1;
	line = NULL;
	while (!ft_strchr(line, '\n') && nb_read != 0)
	{
		buffer = (char *) malloc(sizeof(*buffer) * (1 + 1));
		if (buffer == NULL)
		{
			if (line)
				free(line);
			return (NULL);
		}
		nb_read = read(fd, buffer, 1);
		if (nb_check(nb_read, line, buffer) == 1)
			return (line);
		if (nb_check(nb_read, line, buffer) == 0)
			return (NULL);
		buffer[nb_read] = '\0';
		line = ft_strjoin(line, buffer);
		free(buffer);
	}
	return (line);
}
