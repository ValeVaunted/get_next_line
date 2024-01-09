/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgradow <vgradow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:55:51 by vgradow           #+#    #+#             */
/*   Updated: 2024/01/09 13:00:14 by vgradow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_append(char *static_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(static_buffer, read_buffer);
	free(static_buffer);
	return (temp);
}

char	*store_remainder(char *static_buffer)
{
	int		i;
	int		k;
	char	*new_buffer;

	i = 0;
	k = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	if (!static_buffer[i])
		return (free(static_buffer), NULL);
	new_buffer = ft_calloc(sizeof(char), (ft_strlen(static_buffer) - i) + 1);
	if (!new_buffer)
		return (free(static_buffer), NULL);
	i++;
	while (static_buffer[i])
	{
		new_buffer[k] = static_buffer[i];
		i++;
		k++;
	}
	free(static_buffer);
	return (new_buffer);
}

char	*get_line(char *static_buffer)
{
	int		i;
	char	*new_line;

	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
		i++;
	new_line = ft_calloc(sizeof(char), i + 2);
	if (!new_line)
		return (NULL);
	i = 0;
	while (static_buffer[i] && static_buffer[i] != '\n')
	{
		new_line[i] = static_buffer[i];
		i++;
	}
	if (static_buffer[i] && static_buffer[i] == '\n')
		new_line[i] = static_buffer[i];
	return (new_line);
}

char	*store_file(int fd, char *static_buffer)
{
	ssize_t	chars_read;
	char	*read_buffer;

	read_buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!read_buffer)
		return (free(read_buffer), NULL);
	chars_read = read(fd, read_buffer, BUFFER_SIZE);
	while (chars_read > 0)
	{
		static_buffer = ft_append(static_buffer, read_buffer);
		if (ft_strchr(read_buffer, '\n') != 0)
			break ;
		chars_read = read(fd, read_buffer, BUFFER_SIZE);
	}
	if (chars_read <= 0 && static_buffer[0] == '\0')
		return (free(static_buffer), NULL);
	free(read_buffer);
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*next_line;

	if (static_buffer == NULL)
	{
		static_buffer = ft_calloc(1, 1);
		if (!static_buffer)
			return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(static_buffer);
		static_buffer = NULL;
		return (NULL);
	}
	static_buffer = store_file(fd, static_buffer);
	if (!static_buffer)
		return (NULL);
	next_line = get_line(static_buffer);
	if (!next_line)
		return (free(static_buffer), static_buffer = NULL, NULL);
	static_buffer = store_remainder(static_buffer);
	return (next_line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		count;

// 	count = 0;
// 	fd = open("file1.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	next_line = get_next_line(fd);
// 	printf("%s\n", next_line);
// 	printf("%s\n", next_line);
// 	printf("%s\n", next_line);
// 	printf("%s\n", next_line);
// 	printf("%s\n", next_line);
// 	printf("%s\n", next_line);
// 	printf("%s\n", next_line);
// 	free(next_line);
// 	close(fd);
// 	return (0);
// }
