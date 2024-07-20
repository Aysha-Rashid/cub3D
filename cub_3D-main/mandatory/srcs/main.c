/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:29:51 by mawad             #+#    #+#             */
/*   Updated: 2024/05/21 19:41:29 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_angle(t_game *game)
{
	int	x;
	int	y;

	x = game->player_posx;
	y = game->player_posy;
	if (game->map[y][x] == 'N')
		game->player_angle = 0;
	else if (game->map[y][x] == 'E')
		game->player_angle = 1.5709;
	else if (game->map[y][x] == 'S')
		game->player_angle = 3.14159;
	else if (game->map[y][x] == 'W')
		game->player_angle = 4.71239;
}

void	init_params(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
		game->album[i++].img = NULL;
	game->data.img.img_ptr = NULL;
	game->data.mlx_ptr = mlx_init();
	game->screen_height = SCREEN_HEIGHT;
	game->screen_width = SCREEN_WIDTH;
	game->data.win_ptr = mlx_new_window(game->data.mlx_ptr,
			game->screen_width, game->screen_height, "cub3D");
	game->player_count = 0;
	game->map = NULL;
	game->ceiling_color = -1;
	game->floor_color = -1;
	game->map_ind_height = 0;
	game->map_ind_width = 0;
	game->player_angle = 0;
	game->move_up = FALSE;
	game->move_down = FALSE;
	game->move_right = FALSE;
	game->move_left = FALSE;
	game->rot_left = FALSE;
	game->rot_right = FALSE;
}

void	mini_initial_parse(t_game *game, int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nMust use strictly 2 arguments\n");
		exit(1);
	}
	if (valid_file_name(argv[1]) == FALSE)
	{
		printf("Error\nMap must be given in .cub format\n");
		exit(1);
	}
	game->fd = open(argv[1], O_RDONLY, 0777);
	if (game->fd == -1)
	{
		printf("Error\nCouldn't open file\n");
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	t_game	game;	

	mini_initial_parse(&game, argc, argv);
	init_params(&game);
	parse_elements(&game, game.fd);
	game.data.img.img_ptr = mlx_new_image(game.data.mlx_ptr,
			game.screen_width, game.screen_height);
	if (game.data.img.img_ptr == NULL)
		return (printf("Error\nCouldn't allocate backdrop img ptr\n"), 1);
	game.data.img.img_pixels_ptr = (int *)
		mlx_get_data_addr(game.data.img.img_ptr,
			&(game.data.img.bits_per_pixel), &(game.data.img.line_len),
			&(game.data.img.endian));
	if (game.data.img.img_pixels_ptr == NULL)
		return (printf("Error\nCouldn't allocate img pxl ptr\n"), 1);
	init_angle(&game);
	mlx_hook(game.data.win_ptr, 2, 1L << 0, key_press, &game);
	mlx_hook(game.data.win_ptr, 3, 1L << 1, key_release, &game);
	mlx_hook(game.data.win_ptr, 17, 0, ft_destroy, &game);
	mlx_loop_hook(game.data.mlx_ptr, ray_cast, &game);
	mlx_loop(game.data.mlx_ptr);
	return (0);
}
