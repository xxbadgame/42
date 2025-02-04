/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:46:14 by yannis            #+#    #+#             */
/*   Updated: 2025/02/04 13:50:59 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mini_segments(t_data_points *data_points, t_segment_points *seg_points,
		t_data_img *img, t_lines *lines)
{
	iso_projection(data_points->x * data_points->d_px, data_points->y
		* data_points->d_px, calc_z(lines->split_line[data_points->x],
			&seg_points->color), data_points);
	if (lines->split_line[data_points->x + 1] != NULL)
		find_end_points(data_points, img, seg_points, lines->split_line);
	if (lines->next_line != NULL)
		find_next_end_points(data_points, img, seg_points, lines->next_line);
}

void	change_lines(t_lines *lines)
{
	char	*tmp;

	free_split(lines->split_line);
	tmp = lines->line;
	lines->line = lines->next_line;
	free(tmp);
}

int	split_line_and_next(t_lines *lines, int fd)
{
	lines->split_line = ft_split(lines->line, ' ');
	if (!lines->split_line)
		return (free(lines->line), -1);
	lines->next_line = get_next_line(fd);
	return (0);
}
