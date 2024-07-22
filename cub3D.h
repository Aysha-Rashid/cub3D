/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayal-ras <ayal-ras@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:17:47 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/22 22:42:20 by ayal-ras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include "minilibx/mlx.h"
#define INVALID "Invalid number of arguments"
#define WRONG_EXTEN "Should be cub extension"
#define WRONG_TEX_EXTEN "Should be xpm extension"
#define WRONG_FILE "Can't open the file"
#define WRONG_TEXTFILE "Texture file cannot be opened"
#define EMPTY_FILE "Nothing to read from the file"
#define INVALID_MAP "Something wrong with the map"
#define TEXTURE_ERROR "Something wrong with the texture"
#define DUP "Duplicate found"
#define SYNTAX_ISSUE "Something wrong with values of ceiling or floor"

#define SO 0
#define WE 1
#define EA 2
#define NO 3
#define C 4
#define F 5
// typedef struct s_image
// {
// }				t_image;

typedef struct s_mlx
{
	int		fixed_height;
	int		fixed_width;
	void	*win;
	void	*ptr;
	int		*img_pixels_ptr;
	int		bpp;
	int		size_line;
	int		endian;
	void	*img;
}				t_mlx;

typedef struct s_image
{
	t_mlx	texture[6];
	int		floor;
	int		ceiling;
	// char	*south;
	// char	*west;
	// char	*east;
	// char	*north;
	// int		ceiling;
	// int		floor;
	// char	*text_file_name[5];
	t_mlx   img;
}				t_image;
typedef struct s_coor
{
	int		x;
	int		y;
	int		width;
	int		height;
}				t_coor;

typedef struct s_data
{
	t_image	image;
	t_coor	coord;
	t_mlx	mlx;
	int		file;
}				t_data;

int		esc_key(int key, t_mlx *matrix);
int		check_name(char *argv);
void	exit_error(char *error, t_data *data);
void    read_map(int file, t_data *data);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strcpy(char *dest, char *str);
//utils
int		skip_space_and_count(char *line);
void	check_texture(t_data *data);
int		check_for_syntax(char *str);
int		set_color(char *str);