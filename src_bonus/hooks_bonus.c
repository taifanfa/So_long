/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:07:12 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/12 16:07:14 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

#ifndef KEY_ESC
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
#endif

int	game_loop(t_game *game)
{
	game->frame_counter++;
	if (game->frame_counter >= ENEMY_START_DELAY && \
		game->frame_counter % ENEMY_MOVE_DELAY == 0)
	{
		move_enemies(game);
	}
	render_game(game);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (!game)
		return (0);
	if (keycode == KEY_ESC)
		return (close_game(game));
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	return (0);
}

static void	cleanup_game(t_game *game)
{
	destroy_animations(game);
	destroy_images(game);
	if (game->enemies)
	{
		free(game->enemies);
		game->enemies = NULL;
	}
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_map(game->map);
}

int	close_game(t_game *game)
{
	if (!game)
		exit(0);
	cleanup_game(game);
	exit(0);
	return (0);
}

void	setup_hooks(t_game *game)
{
	if (!game || !game->win)
		return ;
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
