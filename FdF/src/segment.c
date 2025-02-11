/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 06:36:32 by yannis            #+#    #+#             */
/*   Updated: 2025/02/11 10:03:33 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	decision_loop_one(t_segment_points *seg_points, t_data_img *img,
		int color)
{
	while (seg_points->x1 != seg_points->x2)
	{
		my_mlx_pixel_put(img, seg_points->x1, seg_points->y1, color);
		if (seg_points->decision >= 0)
		{
			seg_points->y1 += seg_points->sign_y;
			seg_points->decision -= 2 * seg_points->delta_x;
		}
		seg_points->decision += 2 * seg_points->delta_y;
		seg_points->x1 += seg_points->sign_x;
	}
}

void	decision_loop_two(t_segment_points *seg_points, t_data_img *img,
		int color)
{
	while (seg_points->y1 != seg_points->y2)
	{
		my_mlx_pixel_put(img, seg_points->x1, seg_points->y1, color);
		if (seg_points->decision >= 0)
		{
			seg_points->x1 += seg_points->sign_x;
			seg_points->decision -= 2 * seg_points->delta_y;
		}
		seg_points->decision += 2 * seg_points->delta_x;
		seg_points->y1 += seg_points->sign_y;
	}
}

void	segment_plot(t_segment_points *seg_points, t_data_img *img, int color)
{
	seg_points->delta_x = ft_abs(seg_points->x2 - seg_points->x1);
	seg_points->delta_y = ft_abs(seg_points->y2 - seg_points->y1);
	if (seg_points->x2 > seg_points->x1)
		seg_points->sign_x = 1;
	else
		seg_points->sign_x = -1;
	if (seg_points->y2 > seg_points->y1)
		seg_points->sign_y = 1;
	else
		seg_points->sign_y = -1;
	seg_points->decision = 2 * seg_points->delta_y - seg_points->delta_x;
	if (seg_points->delta_x > seg_points->delta_y)
		decision_loop_one(seg_points, img, color);
	else
		decision_loop_two(seg_points, img, color);
}

void	find_end_points(t_data_points *data_points, t_data_img *img,
		t_segment_points *seg_points, char **split_line)
{
	iso_next_projection((data_points->x + 1) * data_points->d_px, data_points->y
		* data_points->d_px, ft_atoi(split_line[data_points->x + 1]),
		data_points);
	offset_points(seg_points, data_points);
	segment_plot(seg_points, img, seg_points->color);
}

int	find_next_end_points(t_data_points *data_points, t_data_img *img,
		t_segment_points *seg_points, char *next_line)
{
	char	**next_split;

	next_split = ft_split(next_line, ' ');
	if (!next_split)
		return (-1);
	if (len_split(next_split) != img->total_column)
		return (free_split(next_split), -1);
	iso_next_projection(data_points->x * data_points->d_px, (data_points->y + 1)
		* data_points->d_px, ft_atoi(next_split[data_points->x]), data_points);
	free_split(next_split);
	offset_points(seg_points, data_points);
	segment_plot(seg_points, img, seg_points->color);
	return (0);
}
