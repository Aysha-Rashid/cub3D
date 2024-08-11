/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rosman <rosman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:17:47 by ayal-ras          #+#    #+#             */
/*   Updated: 2024/08/10 21:35:20 by rosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
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

#define NO 0
#define SO 1
#define EA 2
#define WE 3
#define C 4
#define F 5
#define N_D0 0
#define E_D90 1.5709
#define S_D180 3.14159
#define W_D270 4.71239
#define SCREEN_HEIGHT 1000
#define SCREEN_WIDTH 1000

#define SPEED 0.03

#define W_KEY 13
#define A_KEY 0
#define S_KEY 1
#define D_KEY 2
#define L_ARROW 123
#define R_ARROW 124
#define ESC_KEY 53

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_wall
{
	void	*img;
	int		*img_pixels_ptr;
	int		fixed_height;
	int		fixed_width;
	int		bpp;
	int		size_line;
	int		endian;
	double	wall_x;
	double	step;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
}				t_wall;

typedef struct s_image
{
	int		floor;
	int		ceiling;
	t_wall	texture[4];
}				t_image;

typedef struct s_pix
{
	double	x;
	double	y;
}				t_pix;

typedef struct s_dda
{
	t_pix	ray_dir;
	t_pix	map;
	double	camera_x;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		start;
	int		end;
	int		line_height;
}				t_dda;

typedef struct s_img_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*img_pixels_ptr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img_mlx;

typedef struct s_data
{
	int			map_width;
	int			map_height;
	int			screen_height;
	int			screen_width;
	int			move_up;
	int			move_down;
	int			move_right;
	int			move_left;
	int			rot_right;
	int			rot_left;
	char		**map;
	char		*paths[4];
	int			path_index;
	int			file;
	double		player_x;
	double		player_y;
	double		player_angle;
	t_image		image;
	t_img_mlx	mlx;
	t_pix		view;
	t_pix		camera;
	int			mouse;
}				t_data;

int		check_name(char *argv);
void	exit_error(char *error, t_data *data);
void	exit_texture(char *message, t_data *data, char *line);
void	read_map(int file, t_data *data);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	check_texture(t_data *data);
int		check_for_syntax(char *str);
int		set_color(char *str, t_data *data);
char	**get_map(t_data *data, int fd);
char	**parse_map(t_data *data, char **map);
void	free_texture(t_data *data, int num);
void	free_map(char **map);
void	put_player(t_data *data);
char	**put_test_map(char **map);
void	dfs(t_data *data, char **test_map, int x, int y);
int		search_corners(t_data *data, t_pos pos, t_pos *four_dir);
int		search_dir(t_data *data, t_pos pos, t_pos *four_dir);
void	checking_after_dfs(t_data *data, char **test_map);
void	init_view(t_data *data);
int		is_trailing_wspace(char *str, int index);
int		check_valid_character(t_data *data, char *map);
int		ft_destroy(t_data *data);
int		ray_cast(void	*param);
void	calc_start_end(t_dda *dda, t_data *data);
void	set_wall(t_data	*data, t_dda *dda, t_wall *tex);
void	drawing_walls(t_data *data, t_dda *dda, t_wall *tex, int slice);
void	drawing_c_f(t_data *data, t_dda *dda, int slice, int color);
int		get_color(t_data *data, int index, int x, int y);
void	my_pixel_put(t_data *data, int x, int y, int color);
void	flush(t_data *data);
void	delta_dist(t_dda *dda);
void	side_dist(t_pix *pos, t_dda *dda);
void	rotate_left_n_right(t_data *data, int dir, int flag);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	moving(t_data *data);
void	put_player_dir(t_data *data, int x, int y);
int		mouse_move(int x, int y, t_data *data);