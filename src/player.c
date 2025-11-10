/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:07:19 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/10 14:24:13 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	move_player(t_game *game, int dx, int dy)
{
	int		nx;
	int		ny;
	char	dest;

	if (!game)
		return ;
	nx = game->player.x + dx;
	ny = game->player.y + dy;
	if (!can_move_to(game, nx, ny))
		return ;
	dest = game->map[ny][nx];
	if (dest == 'E' && handle_exit(game))
		return ;
	if (dest == 'C')
		handle_collectible(game, nx, ny);
	if (dest != 'E')
	{
		game->map[game->player.y][game->player.x] = '0';
		game->map[ny][nx] = 'P';
		game->player.x = nx;
		game->player.y = ny;
	}
	game->player.moves++;
	printf("Moves: %d\n", game->player.moves);
	render_game(game);
}
