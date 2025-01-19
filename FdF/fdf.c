/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:21:40 by yannis            #+#    #+#             */
/*   Updated: 2025/01/19 20:48:02 by yannis           ###   ########.fr       */
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
	int 	zoom_level;
	int		altitude;
	int		total_line;
	int 	total_column;
	char 	*filename;
	int     mouse_pressed;
	int		x_grab;
	int		y_grab;
	double  angle_x;
    double  angle_y;
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

int ft_abs(int nb)
{
	return ((nb > 0) * nb + (nb < 0) * -nb);
}

void segment_plot(int x1, int y1, int x2, int y2, t_data_img *img, int color)
{
	int delta_x;
	int delta_y;
	int sign_x;
	int sign_y;
	int x;
	int y;
	int decision;

	delta_x = ft_abs(x2 - x1);
	delta_y = ft_abs(y2 - y1);

	if (x2 > x1)
		sign_x = 1;
	else
		sign_x = -1;
	if (y2 > y1)
		sign_y = 1;
	else
		sign_y = -1;

	decision = 2 * delta_y - delta_x;
	x = x1;
	y = y1;

	if (delta_x > delta_y) 
	{	
		while (x != x2)
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
		while (y != y2)
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
    *iso_y = 0.5 * (x + y) - z;
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



void draw_image(t_data_img *img, char *filename)
{
	int fd;
    char *line;
    char *next_line;
    char **split_line;
	char **next_split;
	long int color;
    int x, y, z;
    int iso_x, iso_y, iso_x_next, iso_y_next;
    int d_px = 5 * img->zoom_level;
    int offset_x = (img->width / 2);
    int offset_y = ((img->height - (img->total_line * d_px)) / 2);

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
								
			iso_projection(x * d_px, y * d_px, z, &iso_x, &iso_y);	

            if (split_line[x + 1] != NULL)
            {
                iso_projection((x + 1) * d_px, y * d_px, atoi(split_line[x + 1]) + img->zoom_level, &iso_x_next, &iso_y_next);
                segment_plot(iso_x + offset_x, iso_y + offset_y, iso_x_next + offset_x , iso_y_next + offset_y , img, color);
			}
            if (next_line != NULL)
            {
                next_split = ft_split(next_line, ' ');
                iso_projection(x * d_px, (y + 1) * d_px, atoi(next_split[x]) + img->zoom_level, &iso_x_next, &iso_y_next);
                segment_plot(iso_x + offset_x, iso_y + offset_y, iso_x_next + offset_x , iso_y_next + offset_y , img, color);
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
	img.zoom_level = 1;
	img.altitude = 1;
	img.x_grab = 0;
	img.y_grab = 0;
	img.angle_x = 0.0;
    img.angle_y = 0.0;
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
