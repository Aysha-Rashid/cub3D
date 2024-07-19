/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:17:47 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/19 12:52:38 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define INVALID "Invalid number of arguments"
#define WRONG_EXTEN "Should be cub extension"
#define WRONG_TEX_EXTEN "Should be xpm extension"
#define WRONG_FILE "File doesnt exist"
#define WRONG_TEXTFILE "Texture file doesnt exist"
#define EMPTY_FILE "Nothing to read from the file"
#define INVALID_MAP "Something wrong with the map"
#define TEXTURE_ERROR "Something wrong with the texture"

// typedef struct s_image
// {
// }				t_image;
typedef struct s_image
{
	char	*texture[4];
	char	*text_file_name[4];
	int		fixed_height;
	int		fixed_width;
}				t_image;

typedef struct s_mlx
{
	void	*win;
	void	*ptr;
	int		bpp;
	int		size_line;
	int		endian;
	void	*img;
}				t_mlx;

typedef struct s_coor
{
	int		x;
	int		y;
	int		width;
	int		height;
	t_image	image;
}				t_coor;

typedef struct s_data
{
	t_coor	coord;
	int		file;
}				t_data;

int		esc_key(int key, t_mlx *matrix);
int		check_name(char *argv);
void	exit_error(char *error);
void	read_map(int file, t_coor *coord);
char	*get_next_line(int fd);

//utils
int		skip_space_and_count(char *line);