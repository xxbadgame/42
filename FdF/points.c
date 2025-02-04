/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 06:26:21 by yannis            #+#    #+#             */
/*   Updated: 2025/02/04 06:50:24 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1000 && y >= 0 && y < 1000)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

void	iso_projection(int x, int y, int z, t_data_points *data_points)
{
	data_points->iso_x = 0.866 * (x - y);
	data_points->iso_y = 0.52 * (y + x) - z;
}

void	iso_next_projection(int x, int y, int z, t_data_points *data_points)
{
	data_points->iso_x_next = 0.866 * (x - y);
	data_points->iso_y_next = 0.52 * (y + x) - z;
}

int	calc_z(char *line_element, long int *color)
{
	int		index_comma;
	char	*sub1;
	char	*sub2;
	int		result;

	if (ft_strchr(line_element, ',') != NULL)
	{
		index_comma = ft_strchr(line_element, ',') - line_element;
		sub1 = ft_substr(line_element, index_comma + 1,
				ft_strlen(line_element));
		if (!sub1)
			return (-1);
		*color = str_to_hexa(sub1);
		free(sub1);
		sub2 = ft_substr(line_element, 0, index_comma);
		result = ft_atoi(sub2);
		free(sub2);
		return (result);
	}
	else
	{
		*color = 0xFFFFFF;
		return (ft_atoi(line_element));
	}
}

void	offset_points(t_segment_points *seg_points, t_data_points *data_points)
{
	seg_points->x1 = data_points->iso_x + data_points->offset_x;
	seg_points->y1 = data_points->iso_y + data_points->offset_y;
	seg_points->x2 = data_points->iso_x_next + data_points->offset_x;
	seg_points->y2 = data_points->iso_y_next + data_points->offset_y;
}
