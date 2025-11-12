/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:55:52 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/12 13:55:54 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ff_fill(t_flood *flood, int x, int y)
{
	if (x < 0 || y < 0 || x >= flood->width || y >= flood->height)
		return ;
	if (!flood->map[y] || !flood->map[y][x])
		return ;
	if (flood->map[y][x] == '1' || flood->map[y][x] == 'v')
		return ;
	flood->map[y][x] = 'v';
	ff_fill(flood, x + 1, y);
	ff_fill(flood, x - 1, y);
	ff_fill(flood, x, y + 1);
	ff_fill(flood, x, y - 1);
}

char	**dup_map(char **map)
{
	char	**copy;
	int		i;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	find_player_and_count(char **map, int *px, int *py, int *total)
{
	int	y;
	int	x;

	y = 0;
	*px = -1;
	*py = -1;
	*total = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				*px = x;
				*py = y;
			}
			else if (map[y][x] == 'C')
				(*total)++;
			x++;
		}
		y++;
	}
}

int	count_reachable(t_game *game, char **map_cpy, int *found_exit)
{
	int	y;
	int	x;
	int	found_collects;

	y = 0;
	found_collects = 0;
	*found_exit = 0;
	while (map_cpy[y])
	{
		x = 0;
		while (map_cpy[y][x])
		{
			if (game->map[y][x] == 'C' && map_cpy[y][x] == 'v')
				found_collects++;
			if (game->map[y][x] == 'E' && map_cpy[y][x] == 'v')
				*found_exit = 1;
			x++;
		}
		y++;
	}
	return (found_collects);
}

int	check_path_result(int found, int total, int exit)
{
	if (found != total || !exit)
	{
		print_error("Map validation failed: unreachable items");
		return (0);
	}
	return (1);
}
