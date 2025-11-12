/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:01:12 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/12 14:01:14 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "../gnl/get_next_line_bonus.h"

static int	count_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

static void	remove_newline(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
}

char	**read_map_file(const char *filename)
{
	int		fd;
	int		lines;
	char	**map;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = count_lines(fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (close(fd), NULL);
	i = 0;
	while (i < lines)
	{
		map[i] = get_next_line(fd);
		remove_newline(map[i]);
		i++;
	}
	map[i] = NULL;
	return (close(fd), map);
}

char	**load_map(const char *filename, t_game *game)
{
	char	**map;

	map = read_map_file(filename);
	if (!map)
	{
		print_error("Failed to read map");
		return (NULL);
	}
	game->map_h = get_map_height(map);
	game->map_w = get_map_width(map);
	return (map);
}
