/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:50:35 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/12 16:12:44 by tmorais-         ###   ########.fr       */
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

static void	validate_enemy_position(t_game *game, int x, int y)
{
	if (x == game->player.x && y == game->player.y)
	{
		printf("ERROR: Enemy at same position as player!\n");
		print_error("Enemy cannot spawn on player position!");
		close_game(game);
	}
}

static int	is_adjacent_to_player(t_game *game, int x, int y)
{
	int	px;
	int	py;

	px = game->player.x;
	py = game->player.y;
	if ((x == px + 1 && y == py) || (x == px - 1 && y == py))
		return (1);
	if ((x == px && y == py + 1) || (x == px && y == py - 1))
		return (1);
	return (0);
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
				validate_enemy_position(game, x, y);
				if (is_adjacent_to_player(game, x, y))
					print_error("Warning: Enemy spawned adjacent to player!");
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

static int	get_next_direction(int current_dir)
{
	if (current_dir)
		return (0);
	return (1);
}

static void	check_player_collision(t_game *game, int nx, int ny)
{
	if (nx == game->player.x && ny == game->player.y)
	{
		if (game->player.moves == 0)
			return ;
		printf("!!! ENEMY TOUCHED PLAYER !!!\n");
		printf("Game Over! An enemy caught you!\n");
		close_game(game);
	}
}

static int	is_blocked_by_enemy(t_game *game, int idx, int nx, int ny)
{
	int	j;

	j = 0;
	while (j < game->enemy_count)
	{
		if (j != idx && game->enemies[j].x == nx && game->enemies[j].y == ny)
		{
			printf("Enemy %d: blocked by enemy %d, reversing\n", idx, j);
			return (1);
		}
		j++;
	}
	return (0);
}

static int	can_enemy_move(t_game *game, int idx, int nx, int ny)
{
	if (nx < 0 || nx >= game->map_w || ny < 0 || ny >= game->map_h)
	{
		printf("Enemy %d: out of bounds, reversing\n", idx);
		return (0);
	}
	if (game->map[ny][nx] == '1' || game->map[ny][nx] == 'E'
		|| game->map[ny][nx] == 'C')
	{
		printf("Enemy %d: blocked by '%c', reversing\n", idx, game->map[ny][nx]);
		return (0);
	}
	if (is_blocked_by_enemy(game, idx, nx, ny))
		return (0);
	return (1);
}

static void	perform_enemy_move(t_game *game, int i, int nx, int ny)
{
	printf("Enemy %d: moving from [%d][%d] to [%d][%d]\n",
		i, game->enemies[i].y, game->enemies[i].x, ny, nx);
	if (game->map[game->enemies[i].y][game->enemies[i].x] == 'M')
		game->map[game->enemies[i].y][game->enemies[i].x] = '0';
	game->enemies[i].x = nx;
	game->enemies[i].y = ny;
	game->map[ny][nx] = 'M';
	check_player_collision(game, nx, ny);
}

static void	move_single_enemy(t_game *game, int i)
{
	int	nx;
	int	ny;

	if (game->enemies[i].direction)
		nx = game->enemies[i].x + 1;
	else
		nx = game->enemies[i].x - 1;
	ny = game->enemies[i].y;
	if (!can_enemy_move(game, i, nx, ny))
	{
		game->enemies[i].direction = get_next_direction(game->enemies[i].direction);
		return ;
	}
	perform_enemy_move(game, i, nx, ny);
}

void	move_enemies(t_game *game)
{
	int	i;

	if (!game || !game->enemies)
		return ;
	i = 0;
	while (i < game->enemy_count)
	{
		move_single_enemy(game, i);
		i++;
	}
	printf("=== MOVE_ENEMIES FINISHED ===\n\n");
}
