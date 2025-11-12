/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:52:10 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/10 15:00:11 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	validate_paths(t_game *game)
{
	t_flood		flood;
	t_pathcheck	p;

	if (!game || !game->map)
		return (0);
	flood.map = dup_map(game->map);
	if (!flood.map)
		return (print_error("Memory allocation failed in validate_paths"), 0);
	find_player_and_count(flood.map, &p.px, &p.py, &p.total_collects);
	if (p.px == -1 || p.py == -1)
	{
		free_map(flood.map);
		return (print_error("Player not found for flood fill"), 0);
	}
	flood.width = game->map_w;
	flood.height = game->map_h;
	ff_fill(&flood, p.px, p.py);
	p.found_collects = count_reachable(game, flood.map, &p.found_exit);
	game->collectibles = p.total_collects;
	free_map(flood.map);
	return (check_path_result(p.found_collects, p.total_collects, \
		p.found_exit));
}
