/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:21:40 by yannis            #+#    #+#             */
/*   Updated: 2024/12/02 01:54:07 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void    *mlx;
    void    *mlx_win;
}				t_data;


// Création d'un pixel
void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
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

void segment_plot(int x1, int y1, int x2, int y2, t_data *img)
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
			my_mlx_pixel_put(img, x, y, 0xFFFFFF);
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
			my_mlx_pixel_put(img, x, y, 0xFFFFFF);
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

// la point de vue isométrique
void iso_projection(int x, int y, int z, int *iso_x, int *iso_y)
{
    *iso_x = (int)(0.866 * (x - y)); // cos(30°) = 0.866
    *iso_y = (int)(0.5 * (x + y) - z); // sin(30°) = 0.5
}

// lecture de toutes les lignes du fichier
int parse_line_to_pixels(char *filename, t_data *img)
{
    int fd;
	int x;
	int y;
	int z;
	int iso_x1, iso_y1, iso_x2, iso_y2;
	int d_px;
    char *line;
	char *next_line;
	char **split_line;

	y = 0;
	x = 0;
	z = 0;
	d_px = 30;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (-1);
    }

	line = get_next_line(fd);
	next_line = get_next_line(fd);
	while (line != NULL)
	{
		x = 0;
		split_line = ft_split(line, ' ');
		while (split_line[x] != NULL)
		{

			z = ft_atoi(split_line[x]);
			// calcul iso de chaque point de départ si il a une hauteur z ou non
			iso_projection(x * d_px, y * d_px, z, &iso_x1, &iso_y1);

			// seg horizontaux
			if (split_line[x + 1] != NULL)
			{
				int iso_x_next, iso_y_next;
				// on calcul le suivant pour savoir si il a une hauteur pour bien tracer le segement
                iso_projection((x + 1) * d_px, y * d_px, atoi(split_line[x + 1]), &iso_x_next, &iso_y_next);
                segment_plot(iso_x1+300, iso_y1+300, iso_x_next+300, iso_y_next+300, img);
			}

			// seg verticaux
			if (next_line != NULL)
			{
				char **next_split = ft_split(next_line, ' ');
                int iso_x_next, iso_y_next;
				// on calcul le suivant pour savoir si il a une hauteur pour bien tracer le segement
                iso_projection(x * d_px, (y + 1) * d_px, atoi(next_split[x]), &iso_x_next, &iso_y_next);
                segment_plot(iso_x1+300, iso_y1+300, iso_x_next+300, iso_y_next+300, img);
			}
			x++;
		}
		
		free(line);
		// free_split;
		line = next_line;
		next_line = get_next_line(fd);
		y++;
	}
    close(fd);
    return (0);
}

// pixel dans la map depuis .fdf : getnextline appeler une fois : y = 0 et x = pos dans le char *
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
    int     i;

    i = 0;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 1000, 1000, "Hello world!");
	img.img = mlx_new_image(img.mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	parse_line_to_pixels("test_maps/42.fdf", &img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	//mlx_mouse_hook(img.mlx_win, deal_mouse, &img);
	mlx_loop(img.mlx);
}