/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:09:23 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/10 12:09:25 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_width(char **map)
{
	int	width;

	if (!map || !map[0])
		return (0);
	width = ft_strlen(map[0]);
	return (width);
}

int	get_map_height(char **map)
{
	int	height;

	height = 0;
	while (map && map[height])
		height++;
	return (height);
}
