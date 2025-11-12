/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:00:00 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/11 12:00:00 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	load_player_animations(t_game *game)
{
	int	size;

	size = TILE_SIZE;
	game->player.anim.frames[0] = mlx_xpm_file_to_image(game->mlx,
			"textures/bonus/player_up_1.xpm", &size, &size);
	game->player.anim.frames[1] = mlx_xpm_file_to_image(game->mlx,
			"textures/bonus/player_up_2.xpm", &size, &size);
	game->player.anim.frames[2] = mlx_xpm_file_to_image(game->mlx,
			"textures/bonus/player_down_1.xpm", &size, &size);
	game->player.anim.frames[3] = mlx_xpm_file_to_image(game->mlx,
			"textures/bonus/player_down_2.xpm", &size, &size);
	game->player.anim.frames[4] = mlx_xpm_file_to_image(game->mlx,
			"textures/bonus/player_left_1.xpm", &size, &size);
	game->player.anim.frames[5] = mlx_xpm_file_to_image(game->mlx,
			"textures/bonus/player_left_2.xpm", &size, &size);
	game->player.anim.frames[6] = mlx_xpm_file_to_image(game->mlx,
			"textures/bonus/player_right_1.xpm", &size, &size);
	game->player.anim.frames[7] = mlx_xpm_file_to_image(game->mlx,
			"textures/bonus/player_right_2.xpm", &size, &size);
	game->player.anim.current = 0;
	game->player.anim.frame_count = 8;
}

void	*get_player_sprite(t_game *game)
{
	int	base;
	int	frame;

	base = game->player.direction * 2;
	frame = (game->frame_counter / 30) % 2;
	return (game->player.anim.frames[base + frame]);
}

void	destroy_animations(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->player.anim.frame_count)
	{
		if (game->player.anim.frames[i])
			mlx_destroy_image(game->mlx, game->player.anim.frames[i]);
		i++;
	}
}
