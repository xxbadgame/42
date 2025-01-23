/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:21:40 by yannis            #+#    #+#             */
/*   Updated: 2025/01/23 15:30:59 by ynzue-es         ###   ########.fr       */
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
    {
        perror("Error opening file");
        return (-1);
    }
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
	close(fd);
	return (0);
}

typedef struct s_iso_segment_points
{
	int iso_x;
	int iso_y;
	int iso_x_next;
	int iso_y_next;
} t_iso_segment_points;



void draw_image(t_data_img *img, char *filename)
{
	int fd;
    char *line;
    char *next_line;
    char **split_line;
	char **next_split;
	long int color;
    int x, y, z;
    int d_px = 30;
    int offset_x = (img->width / 2);
    int offset_y = ((img->height - (img->total_line * d_px)) / 2);
	t_segment_points seg_points;
	t_iso_segment_points iso_seg_points;

	fd = open(filename, O_RDONLY);
    mlx_destroy_image(img->mlx, img->img);
    img->img = mlx_new_image(img->mlx, img->width, img->height);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	line = get_next_line(fd);
    next_line = get_next_line(fd);
    y = 0;
    while (line != NULL)
    {
        x = 0;
        split_line = ft_split(line, ' ');
        while (split_line[x] != NULL)
        {

			if (ft_strchr(split_line[x], ',') != NULL)
			{
				int index_comma = ft_strchr(split_line[x], ',') - split_line[x];
				z = ft_atoi(ft_substr(split_line[x], 0, index_comma)) + img->altitude;
				color = str_to_hexa(ft_substr(split_line[x], index_comma + 1, ft_strlen(split_line[x])));
			}
			else if (ft_atoi(split_line[x]) > 0 && ft_strchr(split_line[x], ',') == NULL)
			{
				z = ft_atoi(split_line[x]) + img->altitude;
				color = 0xFFFFFF;
			}
			else
			{
				z = ft_atoi(split_line[x]);
				color = 0xFFFFFF;
			}            	
								
			iso_projection(x * d_px, y * d_px, z, &iso_seg_points.iso_x, &iso_seg_points.iso_y);	

            if (split_line[x + 1] != NULL)
            {
                iso_projection((x + 1) * d_px, y * d_px, atoi(split_line[x + 1]), &iso_seg_points.iso_x_next, &iso_seg_points.iso_y_next);
				seg_points.x1 = iso_seg_points.iso_x + offset_x;
				seg_points.y1 = iso_seg_points.iso_y + offset_y;
				seg_points.x2 = iso_seg_points.iso_x_next + offset_x;
				seg_points.y2 = iso_seg_points.iso_y_next + offset_y;
                segment_plot(&seg_points, img, color);
			}
            if (next_line != NULL)
            {
                next_split = ft_split(next_line, ' ');
                iso_projection(x * d_px, (y + 1) * d_px, atoi(next_split[x]), &iso_seg_points.iso_x_next, &iso_seg_points.iso_y_next);
                seg_points.x1 = iso_seg_points.iso_x + offset_x;
				seg_points.y1 = iso_seg_points.iso_y + offset_y;
				seg_points.x2 = iso_seg_points.iso_x_next + offset_x;
				seg_points.y2 = iso_seg_points.iso_y_next + offset_y;
                segment_plot(&seg_points, img, color);
            }
            x++;
        }
        free(line);
        line = next_line;
        next_line = get_next_line(fd);
        y++;
    }
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
	
	img.filename = "test_maps/42.fdf";
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
