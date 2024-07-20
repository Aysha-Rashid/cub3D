/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawad <mawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:56:59 by ytapano           #+#    #+#             */
/*   Updated: 2024/05/25 18:28:08 by mawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_map(t_game *game, int fd)
{
	char	**mark_map;

	game->map = get_map(game, fd);
	parse_map_lines(game, game->map);
	game->map = ft_realloc_x(game, game->map);
	if (game->map_ind_width < 3 || game->map_ind_height < 3)
		exit_err(game, NULL, "map must have a width and height of at least 3");
	set_up_player(game);
	mark_map = mark_map_spawn(game, game->map);
	dfs(game, mark_map, (int) game->player_posx, (int) game->player_posy);
	parse_marked_map(game, mark_map);
	destroy_2d_arr(mark_map);
}

// void	alpha_map_parse(t_game *game, char **map)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	while (map[0][j])
// 	{
// 		if (map[0][j] == '0')
// 			exit_err(game, NULL, "Map not surrounded by walls!");
// 		j++;
// 	}
// 	i = 0;
// 	j = 0;
// 	while (map[i + 1])
// 		i++;
// 	while (map[i][j])
// 	{
// 		if (map[0][j] == '0')
// 			exit_err(game, NULL, "Map not surrounded by walls!");
// 		j++;
// 	}
// }

// void	parse_map(t_game *game, int fd)
// {
// 	game->map = get_map(fd);

// 	if (game->map)
// 	{
// 		for (int i = 0; game->map[i] != NULL; i++) {
// 			printf("%s\n", game->map[i]);
// 		}
// 	}
// 	parse_map_lines(game, game->map);

// 	printf("\n");

// 	game->map = ft_realloc_x(game, game->map);
// 	for (int i = 0; game->map[i] != NULL; i++) {
// 		printf("%s\n", game->map[i]);
// 	}

// 	printf("game height is %d and game width is %d\n",
// 		game->map_ind_height, game->map_ind_width);
// 	printf("\n");

// 	char **mark_map = mark_map_spawn(game, game->map);
// 	for (int i = 0; mark_map[i] != NULL; i++) {
// 		printf("%s\n", mark_map[i]);
// 	}

// 	printf("\n");
// 	set_up_player(game);

// 	printf("player pos is at %d and %d\n",
// 		(int) game->player_posx, (int) game->player_posy);

// 	dfs(game, mark_map, (int) game->player_posx, (int) game->player_posy);
// 	for (int i = 0; mark_map[i] != NULL; i++) {
// 		for (int j = 0; mark_map[i][j]; j++)
// 		{
// 			if (mark_map[i][j] == 'T')
// 				printf(GRN"%c"OG, mark_map[i][j]);
// 			else
// 				printf("%c", mark_map[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	parse_marked_map(game, mark_map);
// 	destroy_2d_arr(mark_map);
// 	printf("\n");

// 	printf("Parsing successful\n");
// }
