/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgradow <vgradow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:55:51 by vgradow           #+#    #+#             */
/*   Updated: 2024/01/08 13:48:20 by vgradow          ###   ########.fr       */
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

char	*ft_append(char *full_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(full_buffer, read_buffer);
	free(full_buffer);
	return (temp);
}

char	*store_remainder(char *buffer)
{
	int		i;
	int		k;
	char	*new_buffer;

	i = 0;
	k = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = ft_calloc(sizeof(char), (ft_strlen(buffer) - i) + 1);
	if (!new_buffer)
		return (NULL);
	i++;
	while (buffer[i])
	{
		new_buffer[k] = buffer[i];
		i++;
		k++;
	}
	free(buffer);
	return (new_buffer);
}

char	*get_line(char *buffer)
{
	int		i;
	char	*new_line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new_line = ft_calloc(sizeof(char), i + 2);
	if (!new_line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new_line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		new_line[i] = buffer[i];
	return (new_line);
}

char	*store_file(int fd, char *remainder)
{
	size_t	chars_read;
	char	*read_buffer;
	int		count;

	count = 0;
	read_buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!read_buffer)
		return (NULL);
	chars_read = read(fd, read_buffer, BUFFER_SIZE);
	while (chars_read > 0)
	{
		remainder = ft_append(remainder, read_buffer);
		if (ft_strchr(read_buffer, '\n') != 0)
			break ;
	}
	free(read_buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*next_line;

	buffer = store_file(fd, buffer);
	if (!buffer)
		return (NULL);
	next_line = get_line(buffer);
	buffer = store_remainder(buffer);
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
// 	printf("%s\n", count, next_line);
// 	printf("%s\n", count, next_line);
// 	printf("%s\n", count, next_line);
// 	printf("%s\n", count, next_line);
// 	printf("%s\n", count, next_line);
// 	printf("%s\n", count, next_line);
// 	free(next_line);
// 	close(fd);
// 	return (0);
// }
