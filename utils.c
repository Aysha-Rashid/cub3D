/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:19:32 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/02 13:38:48 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_strcpy(char *dest, char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest [i] = '\0';
}

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

char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	if (buffer == NULL || buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\0';
	line[i] = '\0';
	return (line);
}
