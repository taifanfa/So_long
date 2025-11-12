/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 16:08:16 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/12 16:08:18 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	can_move_to(t_game *game, int x, int y)
{
	if (!game || !game->map)
		return (0);
	if (y < 0 || x < 0 || y >= game->map_h || x >= game->map_w)
		return (0);
	if (game->map[y][x] == '1')
		return (0);
	return (1);
}

static void	update_player_direction(t_game *game, int dx, int dy)
{
	if (dy == -1)
		game->player.direction = 0;
	else if (dy == 1)
		game->player.direction = 1;
	else if (dx == -1)
		game->player.direction = 2;
	else if (dx == 1)
		game->player.direction = 3;
}

static int	check_enemy_at_position(t_game *game, int x, int y)
{
	int	i;

	if (!game || !game->enemies)
		return (0);
	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
		{
			printf("!!! PLAYER WALKED INTO ENEMY !!!\n");
			printf("Game Over! You touched an enemy!\n");
			close_game(game);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	handle_collectible(t_game *game, int nx, int ny)
{
	game->collectibles--;
	game->map[ny][nx] = '0';
}

static int	handle_exit(t_game *game)
{
	if (game->collectibles == 0)
	{
		printf("You win in %d moves!\n", game->player.moves + 1);
		close_game(game);
		return (1);
	}
	return (0);
}

static void	update_player_position(t_game *game, int nx, int ny, char dest)
{
	if (dest != 'E')
	{
		game->map[game->player.y][game->player.x] = '0';
		game->player.x = nx;
		game->player.y = ny;
		game->map[ny][nx] = 'P';
	}
	game->player.moves++;
	printf("Moves: %d\n", game->player.moves);
}

void	move_player(t_game *game, int dx, int dy)
{
	int		nx;
	int		ny;
	char	dest;

	if (!game)
		return ;
	update_player_direction(game, dx, dy);
	nx = game->player.x + dx;
	ny = game->player.y + dy;
	if (!can_move_to(game, nx, ny))
		return ;
	if (check_enemy_at_position(game, nx, ny))
		return ;
	dest = game->map[ny][nx];
	if (dest == 'E' && handle_exit(game))
		return ;
	if (dest == 'C')
		handle_collectible(game, nx, ny);
	update_player_position(game, nx, ny, dest);
}
