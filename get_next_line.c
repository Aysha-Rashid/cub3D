/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 13:00:25 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/21 20:19:08 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#define BUFFER_SIZE 42

char	*read_line(int fd, char *str)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = malloc(sizeof(char *) * BUFFER_SIZE + 2);
	if (str == NULL)
		str = ft_strdup("");
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		str = ft_strjoin(str, buffer);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*skip_line(char *input_string)
{
	int		i;
	char	*remaining_string;

	i = 0;
	while (input_string[i] != '\0' && input_string[i] != '\n')
		i++;
	if (input_string[i] == '\0')
	{
		free(input_string);
		return (NULL);
	}
	remaining_string = ft_strdup(input_string + i + 1);
	free(input_string);
	return (remaining_string);
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
	{
		line[i] = '\0';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = skip_line(buffer);
	return (line);
}

// int main()
// {
// 	int fd = open("get_next_line.c", O_RDONLY);
//   	char *line = get_next_line(fd);
//   	while (line)
//   	{
//   		printf("%s",line);
//   		free(line);
//  		line = get_next_line(fd);
//  	}
// 	free(line);
// }