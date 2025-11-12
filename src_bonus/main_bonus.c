/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:06:05 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/12 12:12:09 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_w = 0;
	game->map_h = 0;
	game->collectibles = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.moves = 0;
	game->player.direction = 0;
	game->player.anim.current = 0;
	game->player.anim.frame_count = 0;
	game->player_count = 0;
	game->exit_count = 0;
	game->collect_count = 0;
	game->frame_counter = 0;
	game->enemies = NULL;
	game->enemy_count = 0;
	game->img_floor = NULL;
	game->img_wall = NULL;
	game->img_player = NULL;
	game->img_exit = NULL;
	game->img_collect = NULL;
	game->img_enemy = NULL;
	game->frame_counter = 0;
}

static int	setup_game(t_game *game, char *path)
{
	init_game(game);
	game->map = load_map(path, game);
	if (!game->map)
		return (0);
	if (!validate_map(game))
	{
		free_map(game->map);
		return (0);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("mlx_init failed");
		free_map(game->map);
		return (0);
	}
	return (1);
}

static void	start_game(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->map_w * TILE_SIZE,
			game->map_h * TILE_SIZE, WIN_TITLE);
	load_images(game);
	load_player_animations(game);
	init_enemies(game);
	render_game(game);
	setup_hooks(game);
	mlx_loop(game->mlx);
	destroy_images(game);
	destroy_animations(game);
	if (game->enemies)
		free(game->enemies);
	free_map(game->map);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Usage: ./so_long <map.ber>");
		return (1);
	}
	if (!setup_game(&game, argv[1]))
		return (1);
	start_game(&game);
	return (0);
}
