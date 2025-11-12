/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmfanfa <tmfanfa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:10:42 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/11 12:19:28 by tmfanfa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	check_valid_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] != '\n' && \
				 !ft_strchr("01PECM", game->map[y][x]))
        return (print_error("Map contains invalid characters."), 0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_rectangular(t_game *game)
{
	int	y;
	int	len;
	int	current_len;

	len = ft_strlen(game->map[0]);
	if (game->map[0][len - 1] == '\n')
		len--;
	y = 1;
	while (game->map[y])
	{
		current_len = ft_strlen(game->map[y]);
		if (game->map[y][current_len - 1] == '\n')
			current_len--;
		if (current_len != len)
			return (print_error("Map is not rectangular."), 0);
		y++;
	}
	game->map_w = len;
	game->map_h = y;
	return (1);
}

static int	check_walls(t_game *game)
{
	int	x;
	int	y;
	int	w;
	int	h;

	w = game->map_w;
	h = game->map_h;
	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			if ((y == 0 || y == h - 1 || x == 0 || x == w - 1)
				&& game->map[y][x] != '1')
				return (print_error("The map is not surrounded by walls."), 0);
		}
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!check_rectangular(game))
		return (0);
	if (!check_valid_chars(game))
		return (0);
	if (!check_counts(game))
		return (0);
	if (!check_walls(game))
		return (0);
	if (!validate_paths(game))
		return (0);
	return (1);
}
