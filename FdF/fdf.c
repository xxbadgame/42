/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:21:40 by yannis            #+#    #+#             */
/*   Updated: 2025/01/25 22:35:00 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void    *mlx;
    void    *mlx_win;
	int		width;
	int		height;
	int		altitude;
	int		total_line;
	int 	total_column;
	char 	*filename;
}				t_data_img;


void	my_mlx_pixel_put(t_data_img *img, int x, int y, int color)
{
	if (x >= 0 && x < 1000 && y >= 0 && y < 1000)
	{
		char	*dst;
		
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

typedef struct s_segment_points
{
	int x1;
	int x2;
	int y1;
	int y2;
} t_segment_points ;

void segment_plot(t_segment_points *seg_points, t_data_img *img, int color)
{
	int delta_x;
	int delta_y;
	int sign_x;
	int sign_y;
	int x;
	int y;
	int decision;

	delta_x = ft_abs(seg_points->x2 - seg_points->x1);
	delta_y = ft_abs(seg_points->y2 - seg_points->y1);

	if (seg_points->x2 > seg_points->x1)
		sign_x = 1;
	else
		sign_x = -1;
	if (seg_points->y2 > seg_points->y1)
		sign_y = 1;
	else
		sign_y = -1;

	decision = 2 * delta_y - delta_x;
	x = seg_points->x1;
	y = seg_points->y1;

	if (delta_x > delta_y) 
	{	
		while (x != seg_points->x2)
		{
			my_mlx_pixel_put(img, x, y, color);
			if (decision >= 0)
			{
				y += sign_y;
				decision -= 2 * delta_x;
			}
			decision += 2 * delta_y;
			x += sign_x;
		}
	}
	else 
	{
		while (y != seg_points->y2)
		{
			my_mlx_pixel_put(img, x, y, color);
			if (decision >= 0)
			{
				x += sign_x;
				decision -= 2 * delta_y;
			}
			decision += 2 * delta_x;
			y += sign_y;
		}
	}
}

void iso_projection(int x, int y, int z, int *iso_x, int *iso_y)
{
    *iso_x = 0.866 * (x - y);
    *iso_y = 0.52 * (x + y) - z;
}

int size_parsing(char *filename, t_data_img *img)
{
	int fd;
	char *line;
	char **split_line;
	img->total_column = 0;
	img->total_line = 0;

	fd = open(filename, O_RDONLY);
    if (fd < 0)
		return (perror("Error opening file"), -1);
	while ((line = get_next_line(fd)))
	{	
		if (img->total_column == 0)
		{
			split_line = ft_split(line, ' ');
			while (split_line[img->total_column])
				img->total_column++;
			free(split_line);
		}
		img->total_line++;
		free(line);
	}
	return (close(fd), 0);
}


int calc_z(char *line_element, t_data_img *img, long int *color)
{
	int index_comma;
	
	if (ft_strchr(line_element, ',') != NULL)
	{
		index_comma = ft_strchr(line_element, ',') - line_element;
		*color = str_to_hexa(ft_substr(line_element, index_comma + 1, ft_strlen(line_element)));
		return ft_atoi(ft_substr(line_element, 0, index_comma)) + img->altitude;
	}
	else if (ft_atoi(line_element) > 0 && ft_strchr(line_element, ',') == NULL)
	{
		*color = 0xFFFFFF;
		return ft_atoi(line_element) + img->altitude;
	}
	else
	{
		*color = 0xFFFFFF;
		return ft_atoi(line_element);
	}
}

typedef struct s_data_points
{
	int x;
	int y;
	int z;
	int iso_x;
	int iso_y;
	int iso_x_next;
	int iso_y_next;
	int offset_x;
	int offset_y;
	int d_px;
	long int color;
} t_data_points;

void offset_points(t_segment_points *seg_points, t_data_points *data_points)
{
	seg_points->x1 = data_points->iso_x + data_points->offset_x;
	seg_points->y1 = data_points->iso_y + data_points->offset_y;
	seg_points->x2 = data_points->iso_x_next + data_points->offset_x;
	seg_points->y2 = data_points->iso_y_next + data_points->offset_y;
}


void find_end_points(t_data_points data_points, t_data_img *img, t_segment_points *seg_points, char **split_line)
{
	iso_projection((data_points.x + 1) * data_points.d_px, data_points.y * data_points.d_px, atoi(split_line[data_points.x + 1]), &data_points.iso_x_next, &data_points.iso_y_next);
	offset_points(seg_points, &data_points);
	segment_plot(seg_points, img, data_points.color);
}

void find_next_end_points(t_data_points data_points, t_data_img *img, t_segment_points *seg_points, char *next_line)
{
	char **next_split;
	
	next_split = ft_split(next_line, ' ');
	iso_projection(data_points.x * data_points.d_px, (data_points.y + 1) * data_points.d_px, atoi(next_split[data_points.x]), &data_points.iso_x_next, &data_points.iso_y_next);
	offset_points(seg_points, &data_points);
	segment_plot(seg_points, img, data_points.color);
}

void create_segments(t_data_points data_points, t_segment_points seg_points,int fd, t_data_img *img)
{
	char *line;
    char *next_line;
    char **split_line;

	line = get_next_line(fd);
    next_line = get_next_line(fd);
    while (line != NULL)
    {
        data_points.x = 0;
        split_line = ft_split(line, ' ');
        while (split_line[data_points.x] != NULL)
        {
			data_points.z = calc_z(split_line[data_points.x], img, &data_points.color);
			iso_projection(data_points.x * data_points.d_px, data_points.y * data_points.d_px, data_points.z, &data_points.iso_x, &data_points.iso_y);
			if (split_line[data_points.x + 1] != NULL)
				find_end_points(data_points, img, &seg_points, split_line);
            if (next_line != NULL)
                find_next_end_points(data_points, img, &seg_points, next_line);
            data_points.x++;
        }
        free(line);
        line = next_line;
        next_line = get_next_line(fd);
        data_points.y++;
    }
}


void draw_image(t_data_img *img, char *filename)
{
	int fd;
	t_data_points data_points;
	t_segment_points seg_points;

    data_points.d_px = 30;
    data_points.offset_x = (img->width / 2);
    data_points.offset_y = ((img->height - (img->total_line * data_points.d_px)) / 2);

	fd = open(filename, O_RDONLY);
    mlx_destroy_image(img->mlx, img->img);
    img->img = mlx_new_image(img->mlx, img->width, img->height);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	
	data_points.y = 0;
	create_segments(data_points, seg_points, fd, img);

    mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	close(fd);
}


int parse_line_to_pixels(char *filename, t_data_img *img)
{
	size_parsing(filename, img);
	draw_image(img, img->filename);
    return (0);
}

int close_window(void *param)
{
	(void)param;
	exit(0);
}

int close_window_escape(int keycode,void *param)
{
	(void)param;
	if (keycode == 65307)
		exit(0);
	return (0);
}

int	main(void)
{
	int 	width;
	int 	height;
	t_data_img	img;
	
	img.filename = "test_maps/20-60.fdf";
	img.altitude = 1;
	height = 1000;
	width = 1000;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, width, height, "FdF ynzue-es");
	img.img = mlx_new_image(img.mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	img.width = width;
	img.height = height;
	parse_line_to_pixels(img.filename, &img);
	mlx_hook(img.mlx_win, 17, 0, close_window, NULL);
	mlx_hook(img.mlx_win, 2, 1L<<0, close_window_escape, NULL);
	mlx_loop(img.mlx);
}
