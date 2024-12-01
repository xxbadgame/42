/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:38:44 by yannis            #+#    #+#             */
/*   Updated: 2024/11/30 22:35:34 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Prendre le fichier fdf et envoyer les lignes pour constituer l'image

int main()
{
    read_fdf_file("test_maps/julia.fdf");
}

/*
int deal_mouse(int button, int x, int y, void *param)
{
	t_data *img = (t_data *)param;
	static int x1;
	static int y1;
	static int i;

	i++;
	printf("click : %d\n", i);
	if (i == 1)
	{
		x1 = x;
		y1 = y;
	}
	if (i == 2)
	{
		printf("point 1 : (%d, %d)\n", x1, y1);
		printf("point 2 : (%d, %d)\n", x, y);

		segment_plot(x1, y1, x, y, img);
		
		i = 0;
	}
	my_mlx_pixel_put(img, x, y, 0xFF0000);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}
*/
