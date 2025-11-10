/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:07:41 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/10 17:25:57 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_game *game)
{
	int	size;

	size = TILE_SIZE;
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&size, &size);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "textures/ground.xpm",
			&size, &size);
	game->img_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&size, &size);
	game->img_collect = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &size, &size);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&size, &size);
}

void	destroy_images(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_collect)
		mlx_destroy_image(game->mlx, game->img_collect);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
}

static void	put_tile(t_game *game, int x, int y, char c)
{
	void	*img;
	int		sx;
	int		sy;

	sx = x * TILE_SIZE;
	sy = y * TILE_SIZE;
	img = game->img_floor;
	if (c == '1')
		img = game->img_wall;
	else if (c == 'P')
		img = game->img_player;
	else if (c == 'C')
		img = game->img_collect;
	else if (c == 'E')
		img = game->img_exit;
	mlx_put_image_to_window(game->mlx, game->win, img, sx, sy);
}

void	render_game(t_game *game)
{
	int	y;
	int	x;

	if (!game || !game->map)
		return ;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			put_tile(game, x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
}
