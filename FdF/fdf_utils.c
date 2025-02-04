/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:38:26 by yannis            #+#    #+#             */
/*   Updated: 2025/02/04 06:49:08 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long int	str_to_hexa(char *str)
{
	int			i;
	long int	result;

	result = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F')
		|| (str[i] >= 'a' && str[i] <= 'f'))
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 16 + (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * 16 + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * 16 + (str[i] - 'a' + 10);
		i++;
	}
	return (result);
}

int	ft_abs(int nb)
{
	return ((nb > 0) * nb + (nb < 0) * -nb);
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
