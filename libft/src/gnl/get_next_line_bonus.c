/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:19:14 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/27 09:33:18 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line_bonus.h"

char	*ft_cleanup_stash(char **stash)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

char	*ft_extract_line(char **stash)
{
	char	*line;
	char	*temp;
	int		i;

	if (!*stash || !**stash)
		return (ft_cleanup_stash(stash));
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	line = ft_substr(*stash, 0, i);
	temp = *stash;
	*stash = ft_strdup(*stash + i);
	free(temp);
	if (*stash && !**stash)
		ft_cleanup_stash(stash);
	return (line);
}

char	*ft_handle_error(char *buf, char **stash)
{
	free(buf);
	return (ft_cleanup_stash(stash));
}

char	*ft_read_buffer(int fd, char **stash)
{
	char	*buf;
	char	*temp;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(*stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (ft_handle_error(buf, stash));
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		temp = *stash;
		*stash = ft_strjoin(*stash, buf);
		if (temp)
			free(temp);
		if (!*stash)
			return (ft_handle_error(buf, NULL));
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_OPEN];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_OPEN)
		return (NULL);
	buf = ft_read_buffer(fd, &stash[fd]);
	if (!buf)
		return (NULL);
	free(buf);
	return (ft_extract_line(&stash[fd]));
}
