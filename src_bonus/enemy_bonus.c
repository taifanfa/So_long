/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:00:00 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/11 12:00:00 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	count_enemies_in_map(char **map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'M')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	position_enemies(t_game *game)
{
	int	y;
	int	x;
	int	idx;

	idx = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'M')
			{
				game->enemies[idx].x = x;
				game->enemies[idx].y = y;
				game->enemies[idx].direction = 0;
				idx++;
			}
			x++;
		}
		y++;
	}
}

void	init_enemies(t_game *game)
{
	int	count;

	count = count_enemies_in_map(game->map);
	if (count == 0)
	{
		game->enemies = NULL;
		game->enemy_count = 0;
		return ;
	}
	game->enemies = malloc(sizeof(t_enemy) * count);
	if (!game->enemies)
	{
		print_error("Failed to allocate memory for enemies");
		close_game(game);
	}
	game->enemy_count = count;
	position_enemies(game);
}

static void	check_enemy_collision(t_game *game, int nx, int ny)
{
	if (nx == game->player.x && ny == game->player.y)
	{
		printf("Game Over! You touched an enemy!\n");
		close_game(game);
	}
}

void	move_enemies(t_game *game)
{
	int	i;
	int	nx;
	int	ny;

	i = 0;
	while (i < game->enemy_count)
	{
		nx = game->enemies[i].x + (game->enemies[i].direction ? 1 : -1);
		ny = game->enemies[i].y;
		if (game->map[ny][nx] == '1' || game->map[ny][nx] == 'E'
			|| game->map[ny][nx] == 'C')
		{
			game->enemies[i].direction = !game->enemies[i].direction;
			i++;
			continue ;
		}
		game->map[game->enemies[i].y][game->enemies[i].x] = '0';
		game->enemies[i].x = nx;
		game->map[ny][nx] = 'M';
		check_enemy_collision(game, nx, ny);
		i++;
	}
}
