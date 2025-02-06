/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:21:40 by yannis            #+#    #+#             */
/*   Updated: 2025/02/06 12:35:10 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	create_segments(t_data_points *data_points, t_segment_points *seg_points,
		int fd, t_data_img *img)
{
	t_lines	lines;

	lines.line = get_next_line(fd);
	if (!lines.line)
		return (-1);
	data_points->y = 0;
	while (lines.line != NULL)
	{
		data_points->x = 0;
		if (split_line_and_next(&lines, fd, img, data_points->y) == -1)
			return (-1);
		while (lines.split_line[data_points->x] != NULL)
		{
			mini_segments(data_points, seg_points, img, &lines);
			data_points->x++;
		}
		change_lines(&lines);
		data_points->y++;
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	}
	free(lines.line);
	return (0);
}

void	zoom_map(t_data_points *data_points, t_data_img *img)
{
	if (img->total_column >= 400 || img->total_line >= 400)
		data_points->d_px = 1;
	else if (img->total_column >= 200 || img->total_line >= 200)
		data_points->d_px = 2;
	else if (img->total_column >= 100 || img->total_line >= 100)
		data_points->d_px = 4;
	else if (img->total_column >= 50 || img->total_line >= 50)
		data_points->d_px = 6;
	else if (img->total_column >= 25 || img->total_line >= 25)
		data_points->d_px = 15;
	else
		data_points->d_px = 20;
}

int	draw_image(t_data_img *img, char *filename)
{
	int					fd;
	t_data_points		data_points;
	t_segment_points	seg_points;

	data_points.d_px = 0;
	zoom_map(&data_points, img);
	data_points.offset_x = (img->width / 2.2);
	data_points.offset_y = ((img->height - (img->total_line * data_points.d_px))
			/ 2);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), -1);
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, img->width, img->height);
	if (!img->img)
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (-1);
	if (create_segments(&data_points, &seg_points, fd, img) == -1)
		return (-1);
	return (close(fd), 0);
}

int	init_fdf(t_data_img *img)
{
	img->mlx = mlx_init();
	if (!img->mlx)
		return (perror("Error: Failed MiniLibX.\n"), -1);
	img->mlx_win = mlx_new_window(img->mlx, img->width, img->height, "FdF");
	if (!img->mlx_win)
		return (perror("Error: Failed window.\n"), -1);
	img->img = mlx_new_image(img->mlx, img->width, img->height);
	if (!img->img)
		return (perror("Error: Failed image.\n"), -1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (perror("Error: Failed adress.\n"), -1);
	if (draw_image(img, img->filename) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data_img	img;

	if (argc != 2)
		return (ft_putendl_fd("Usage : ./fdf_linux <filename>", 1), -1);
	img.filename = argv[1];
	img.width = 1000;
	img.height = 1000;
	if (size_parsing(img.filename, &img) == -1)
		return (-1);
	if (init_fdf(&img) == -1)
		return (close_window(&img), -1);
	mlx_hook(img.mlx_win, 17, 0, close_window, &img);
	mlx_hook(img.mlx_win, 2, 1L << 0, close_window_escape, &img);
	mlx_loop(img.mlx);
}
