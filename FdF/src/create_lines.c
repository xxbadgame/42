/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:46:14 by yannis            #+#    #+#             */
/*   Updated: 2025/02/11 10:06:36 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	mini_segments(t_data_points *data_points, t_segment_points *seg_points,
		t_data_img *img, t_lines *lines)
{
	int	z;

	z = calc_z(lines->split_line[data_points->x], &seg_points->color);
	if(z == -1)
		return (-1);
	iso_projection(data_points->x * data_points->d_px, data_points->y
		* data_points->d_px, z, data_points);
	if (lines->split_line[data_points->x + 1] != NULL)
		find_end_points(data_points, img, seg_points, lines->split_line);
	if (lines->next_line != NULL)
		find_next_end_points(data_points, img, seg_points, lines->next_line);
	return (0);
}

void	change_lines(t_lines *lines)
{
	char	*tmp;

	free_split(lines->split_line);
	tmp = lines->line;
	lines->line = lines->next_line;
	free(tmp);
}

int	split_line_and_next(t_lines *lines, int fd, t_data_img *img, int y)
{
	lines->split_line = ft_split(lines->line, ' ');
	if (!lines->split_line)
		return (free(lines->line), -1);
	if (len_split(lines->split_line) != img->total_column)
		return (perror("Error file format"), free(lines->line),
			free_split(lines->split_line), -1);
	lines->next_line = get_next_line(fd);
	if (!lines->next_line && y >= img->total_line)
		return (free(lines->line), free_split(lines->split_line), -1);
	return (0);
}
