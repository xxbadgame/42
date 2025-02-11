/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:02:10 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/02/11 10:03:27 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

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
	if (!line)
		return (close(fd), -1);
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
	if (bytes_read == -1)
		return (close(fd), -1);
	while (bytes_read == 1)
	{
		if (buffer[0] == '\n')
			img->total_line++;
		bytes_read = read(fd, buffer, sizeof(buffer));
		if (bytes_read == -1)
			return (close(fd), -1);
	}
	if (buffer[0] != '\n')
		img->total_line++;
	return (close(fd), 0);
}

int	size_parsing(char *filename, t_data_img *img)
{
	if (count_columns(filename, img) == -1)
		return (-1);
	ft_putendl_fd("🕓 -> wait for parsing...", 1);
	if (count_lines(filename, img) == -1)
		return (-1);
	ft_putendl_fd("✅ -> parsing complete", 1);
	return (0);
}
