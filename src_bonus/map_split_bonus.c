/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:06:19 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/10 12:06:21 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	*extract_line(char *buf, int start, int end)
{
	int		len;
	int		i;
	char	*line;

	len = end - start;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (++i < len)
		line[i] = buf[start + i];
	line[i] = '\0';
	return (line);
}

static int	count_lines(char *buf)
{
	int	i;
	int	lines;

	if (!buf)
		return (0);
	i = 0;
	lines = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			lines++;
		i++;
	}
	if (i > 0 && buf[i - 1] != '\n')
		lines++;
	return (lines);
}

char	**split_map(char *buf)
{
	int		i;
	int		start;
	int		row;
	int		lines;
	char	**map;

	lines = count_lines(buf);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	i = -1;
	row = 0;
	start = 0;
	while (buf[++i])
	{
		if (buf[i] == '\n')
		{
			map[row++] = extract_line(buf, start, i);
			start = i + 1;
		}
	}
	if (start < i)
		map[row++] = extract_line(buf, start, i);
	map[row] = NULL;
	return (map);
}
