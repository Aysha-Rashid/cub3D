/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:17:47 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/16 22:28:19 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define INVALID "Invalid number of arguments"
#define WRONG_EXTEN "Should be cub extension"
#define WRONG_FILE "File doesnt exist"
#define EMPTY_FILE "Nothing to read from the file"

typedef struct s_image
{
	int		bpp;
	int		size_line;
	int		endian;
	void	*img;
}				t_image;

typedef struct s_mlx
{
	void	*win;
	void	*ptr;
}				t_mlx;

typedef struct s_coor
{
	int	x;
	int	y;
	int	width;
	int	height;
}				t_coor;

typedef struct s_data
{
	t_coor	coord;
	int		file;
	// t_mlx	*mlx;
}				t_data;

int		esc_key(int key, t_mlx *matrix);
int		check_name(char *argv);
void	exit_error(char *error);
char	*get_next_line(int fd);