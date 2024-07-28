/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:17:47 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/07/28 20:34:12 by rosman           ###   ########.fr       */
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
#define MEMORY_ISSUE "allocation failed"
#define COLOR_ISSUE "Same color for Ceiling and Floor"

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
	int		floor;
	int		ceiling;
	t_mlx	texture[6];
}				t_image;

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_pix
{
	double	x;
	double	y;
}				t_pix;

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
	char	**map;
	char	*paths[4];
	int		path_index;
	int		file;
	double	player_x;
	double	player_y;
	t_pix	view;
	t_pix	camera;
}				t_data;

int		esc_key(int key, t_mlx *matrix);
int		check_name(char *argv);
void	exit_error(char *error, t_data *data);
void	read_map(int file, t_data *data);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strcpy(char *dest, char *str);
//utils
int		skip_space_and_count(char *line);
void	check_texture(t_data *data);
int		check_for_syntax(char *str);
int		set_color(char *str, t_data *data);
char	*extract_line(char *buffer);
void	free_map(char **map);
char	**get_map(t_data *data, int fd);
char	**parse_map(t_data *data, char **map);
void	free_texture(t_data *data, int num);
void	free_map(char **map);
void	put_player(t_data *data);
void	print_map(char **map);
char	**put_test_map(char **map);
void	dfs(t_data *data, char **test_map, int x, int y);
int		search_corners(t_data *data, t_pos pos, t_pos *four_dir);
int		search_dir(t_data *data, t_pos pos, t_pos *four_dir);
void	checking_after_dfs(t_data *data, char **test_map);
void	check_boundary(t_data *data, char **test_map, int x, int y);
void	checking_after_dfs(t_data *data, char **test_map);