/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:21:40 by yannis            #+#    #+#             */
/*   Updated: 2025/01/29 19:01:57 by yannis           ###   ########.fr       */
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

int	size_parsing(char *filename, t_data_img *img)
{
	int		fd;
	char	*line;
	char	**split_line;
	char 	*tmp;

	img->total_column = 0;
	img->total_line = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), -1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), -1);
	while (line != NULL)
	{
		if (img->total_column == 0)
		{
			split_line = ft_split(line, ' ');
			if (!split_line)
				return (free(line), close(fd), -1);
			while (split_line[img->total_column])
				img->total_column++;
			free_split(split_line);
		}
		img->total_line++;
		tmp = line;
		line = get_next_line(fd);
		free(tmp);
	}
	free(line);
	return (close(fd), 0);
}

int	calc_z(char *line_element, long int *color)
{
	int	index_comma;

	if (ft_strchr(line_element, ',') != NULL)
	{
		index_comma = ft_strchr(line_element, ',') - line_element;
		*color = str_to_hexa(ft_substr(line_element, index_comma + 1,
					ft_strlen(line_element)));
		return (ft_atoi(ft_substr(line_element, 0, index_comma)));
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

void	find_end_points(t_data_points *data_points, t_data_img *img,
		t_segment_points *seg_points, char **split_line)
{
	iso_next_projection((data_points->x + 1) * data_points->d_px, data_points->y
		* data_points->d_px, atoi(split_line[data_points->x + 1]), data_points);
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
	iso_next_projection(data_points->x * data_points->d_px, (data_points->y + 1)
		* data_points->d_px, atoi(next_split[data_points->x]), data_points);
	free_split(next_split);
	offset_points(seg_points, data_points);
	segment_plot(seg_points, img, seg_points->color);
	return (0);
}

int	create_segments(t_data_points *data_points,
		t_segment_points *seg_points, int fd, t_data_img *img)
{
	char	*line = NULL;
	char	*next_line = NULL;
	char	**split_line;
	char	*tmp;

	line = get_next_line(fd);
	while (line != NULL)
	{
		data_points->x = 0;
		split_line = ft_split(line, ' ');
		if (!split_line)
			return (free(line), -1);
		next_line = get_next_line(fd);
		while (split_line[data_points->x] != NULL)
		{
			iso_projection(data_points->x * data_points->d_px, data_points->y
				* data_points->d_px, calc_z(split_line[data_points->x],
					&seg_points->color), data_points);
			if (split_line[data_points->x + 1] != NULL)
				find_end_points(data_points, img, seg_points, split_line);
			if (next_line != NULL)
				find_next_end_points(data_points, img, seg_points, next_line);
			data_points->x++;
		}
		free_split(split_line);
		tmp = line;
		line = next_line;
		if(tmp)
			free(tmp);
		data_points->y++;
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	}
	free(line);
	return (0);
}

void zoom_map(t_data_points	*data_points, t_data_img *img)
{
	if (img->total_column >= 400 || img->total_line >= 400)
		data_points->d_px = 1;
	else if (img->total_column >= 200 || img->total_line >= 200)
		data_points->d_px = 3;
	else if (img->total_column >= 100 || img->total_line >= 100)
		data_points->d_px = 5;
	else if (img->total_column >= 50 || img->total_line >= 50)
		data_points->d_px = 10;
	else
		data_points->d_px = 20;
}

void	draw_image(t_data_img *img, char *filename)
{
	int					fd;
	t_data_points		data_points;
	t_segment_points	seg_points;

	zoom_map(&data_points, img);
	data_points.offset_x = (img->width / 2);
	data_points.offset_y = ((img->height - (img->total_line * data_points.d_px))
			/ 2);
	fd = open(filename, O_RDONLY);
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	data_points.y = 0;
	create_segments(&data_points, &seg_points, fd, img);
	close(fd);
}

int	close_window(t_data_img *img)
{

	if (img->img)
		mlx_destroy_image(img->mlx, img->img);
	if (img->mlx_win)
		mlx_destroy_window(img->mlx, img->mlx_win);
	if (img->mlx)
	{
		mlx_destroy_display(img->mlx);
		free(img->mlx);
	}
	exit(0);
}

int	close_window_escape(int keycode, t_data_img *img)
{
	if (keycode == 65307)
		close_window(img);
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
	img.mlx = mlx_init();
	if (!img.mlx)
		return (perror("Error: Failed to initialize MiniLibX.\n"), -1);
	img.mlx_win = mlx_new_window(img.mlx, img.width, img.height, "FdF ynzue-es");
	img.img = mlx_new_image(img.mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	size_parsing(img.filename, &img);
	draw_image(&img, img.filename);
	mlx_hook(img.mlx_win, 17, 0, close_window, &img);
	mlx_hook(img.mlx_win, 2, 1L << 0, close_window_escape, &img);
	mlx_loop(img.mlx);
}
