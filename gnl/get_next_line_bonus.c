/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:42:15 by tmorais-          #+#    #+#             */
/*   Updated: 2025/11/10 14:37:52 by tmorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;
	size_t	len;

	if (!buffer || !*buffer)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (len == 0 && buffer[len] != '\n')
		return (NULL);
	if (buffer[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	char	*nl_pos;
	size_t	remaining_len;
	size_t	i;

	nl_pos = ft_strchr_gnl(buffer, '\n');
	if (!nl_pos || !*(nl_pos + 1))
	{
		free(buffer);
		return (NULL);
	}
	nl_pos++;
	remaining_len = ft_strlen_gnl(nl_pos);
	new_buffer = malloc(remaining_len + 1);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i = -1;
	while (++i < remaining_len)
		new_buffer[i] = nl_pos[i];
	new_buffer[i] = '\0';
	free(buffer);
	return (new_buffer);
}

static char	*handle_read_error(char *temp, char *buffer)
{
	free(temp);
	free(buffer);
	return (NULL);
}

static char	*read_and_join(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (handle_read_error(temp, buffer));
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, temp);
		if (!buffer)
			return (handle_read_error(temp, NULL));
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffers[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	buffers[fd] = read_and_join(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = extract_line(buffers[fd]);
	if (!line)
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
		return (NULL);
	}
	buffers[fd] = update_buffer(buffers[fd]);
	return (line);
}
