/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_counts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmfanfa <tmfanfa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:09:50 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/11 11:18:39 by tmfanfa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

static void	count_elements(t_game *game, t_counts *counts)
{
	int	y;
	int	x;

	ft_memset(counts, 0, sizeof(t_counts));
	y = 0;
	while (y < game->map_h)
	{
		x = 0;
		while (x < game->map_w)
		{
			if (game->map[y][x] == 'P')
			{
				counts->players++;
				game->player.x = x;
				game->player.y = y;
			}
			else if (game->map[y][x] == 'E')
				counts->exits++;
			else if (game->map[y][x] == 'C')
				counts->collects++;
			x++;
		}
		y++;
	}
}

int	check_counts(t_game *game)
{
	t_counts	counts;

	count_elements(game, &counts);
	if (counts.players != 1 || counts.exits != 1 || counts.collects < 1)
	{
		print_error("Map must have 1 player, 1 exit and at \
			least 1 collectible");
		return (0);
	}
	return (1);
}
