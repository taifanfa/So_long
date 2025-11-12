/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:07:46 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/12 16:28:54 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	load_basic_images(t_game *game, int size)
{
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&size, &size);
	if (!game->img_wall)
		printf("ERROR: Failed to load wall.xpm\n");
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "textures/ground.xpm",
			&size, &size);
	if (!game->img_floor)
		printf("ERROR: Failed to load ground.xpm\n");
	game->img_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&size, &size);
	if (!game->img_player)
		printf("ERROR: Failed to load player.xpm\n");
}

static void	load_game_images(t_game *game, int size)
{
	game->img_collect = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &size, &size);
	if (!game->img_collect)
		printf("ERROR: Failed to load coin.xpm\n");
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&size, &size);
	if (!game->img_exit)
		printf("ERROR: Failed to load exit.xpm\n");
	game->img_enemy = mlx_xpm_file_to_image(game->mlx, "textures/enemy_1.xpm", \
        &size, &size);
	if (!game->img_enemy)
	{
		printf("CRITICAL: enemy_1.xpm failed to load!\n");
		printf("Check if file exists and has correct XPM format\n");
		close_game(game);  // Feche o jogo em vez de usar fallback
	}
}

void	load_images(t_game *game)
{
	int	size;

	size = TILE_SIZE;
	load_basic_images(game, size);
	load_game_images(game, size);
}

void	destroy_images(t_game *game)
{
	if (!game || !game->mlx)
		return ;
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
	if (game->img_enemy && game->img_enemy != game->img_collect)
		mlx_destroy_image(game->mlx, game->img_enemy);
}

static void	*get_tile_image(t_game *game, char c)
{
	if (c == '1')
		return (game->img_wall);
	else if (c == 'P')
		return (get_player_sprite(game));
	else if (c == 'C')
		return (game->img_collect);
	else if (c == 'E')
		return (game->img_exit);
	else if (c == 'M')
		return (game->img_enemy);
	return (NULL);
}

static void	put_tile(t_game *game, int x, int y, char c)
{
	void	*img;
	int		sx;
	int		sy;

	sx = x * TILE_SIZE;
	sy = y * TILE_SIZE;
	if (c != '1')
		mlx_put_image_to_window(game->mlx, game->win, game->img_floor, sx, sy);
	img = get_tile_image(game, c);
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img, sx, sy);
}

void	render_moves(t_game *game)
{
	char	*moves_str;
	char	*temp;
	int		num;

	num = game->player.moves;
	moves_str = ft_itoa(num);
	temp = ft_strjoin("Moves: ", moves_str);
	free(moves_str);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, temp);
	free(temp);
}

void	render_game(t_game *game)
{
	int	y;
	int	x;

	if (!game || !game->map || !game->win || !game->mlx)
		return ;
	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
			put_tile(game, x, y, game->map[y][x]);
	}
	render_moves(game);
}
