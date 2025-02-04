/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:02:10 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/02/04 06:51:22 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_columns(char *filename, t_data_img *img)
{
	int		fd;
	char	**split_line;
	char	*line;

	img->total_column = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), -1);
	line = get_next_line(fd);
	split_line = ft_split(line, ' ');
	if (!split_line)
		return (free(line), close(fd), -1);
	while (split_line[img->total_column])
		img->total_column++;
	free_split(split_line);
	free(line);
	return (close(fd), 0);
}

int	count_lines(char *filename, t_data_img *img)
{
	int		fd;
	int		bytes_read;
	char	buffer[1];

	img->total_line = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), -1);
	bytes_read = read(fd, buffer, 1);
	while (bytes_read == 1)
	{
		while (buffer[0] != '\n')
			bytes_read = read(fd, buffer, sizeof(buffer));
		bytes_read = read(fd, buffer, sizeof(buffer));
		img->total_line++;
	}
	return (close(fd), 0);
}

int	size_parsing(char *filename, t_data_img *img)
{
	count_lines(filename, img);
	count_columns(filename, img);
	return (0);
}
