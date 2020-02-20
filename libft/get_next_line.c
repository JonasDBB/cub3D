/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbennink <jbennink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 14:06:22 by jbennink       #+#    #+#                */
/*   Updated: 2020/01/30 14:40:19 by jbennink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	gnl_strlen(char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char		*gnl_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

static void		buffer_set(char *orig, char *buffer)
{
	if (*buffer == '\n')
		buffer++;
	while (*buffer != '\0')
	{
		*orig = *buffer;
		buffer++;
		orig++;
	}
	*orig = '\0';
}

static void		*ft_free(char **line)
{
	free(*line);
	return (NULL);
}

static char		*join_line(char *line, char *buffer)
{
	char	*ret;
	char	*orig;
	size_t	i;

	orig = buffer;
	ret = (char *)malloc(gnl_strlen(line) + gnl_strlen(buffer) + 1);
	if (ret == NULL)
		return (ft_free(&line));
	i = 0;
	if (line != NULL)
		while (line[i] != '\0')
		{
			ret[i] = line[i];
			i++;
		}
	free(line);
	while (*buffer != '\0' && *buffer != '\n')
	{
		ret[i] = *buffer;
		buffer++;
		i++;
	}
	ret[i] = '\0';
	buffer_set(orig, buffer);
	return (ret);
}

int				get_next_line(int fd, char **line)
{
	ssize_t		size;
	static char	buffer[BUFFER_SIZE + 1];
	int			ret;

	*line = NULL;
	ret = 0;
	while (ret == 0)
	{
		if (!*buffer)
		{
			size = read(fd, buffer, BUFFER_SIZE);
			if (size <= 0)
			{
				buffer[0] = '\0';
				ret = size;
				*line = (ret == 0) ? join_line(*line, buffer) : NULL;
				break ;
			}
			buffer[size] = '\0';
		}
		ret = (gnl_strchr(buffer, '\n')) ? 1 : ret;
		*line = join_line(*line, buffer);
		ret = (*line == NULL) ? -1 : ret;
	}
	return (ret);
}
