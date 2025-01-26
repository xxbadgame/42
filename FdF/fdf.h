/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yannis <yannis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:07:31 by yannis            #+#    #+#             */
/*   Updated: 2025/01/26 17:49:26 by yannis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
} t_data_points;

typedef struct s_segment_points
{
	int x1;
	int x2;
	int y1;
	int y2;
    int delta_x;
	int delta_y;
	int sign_x;
	int sign_y;
	int decision;
    long int color;
} t_segment_points ;


long int	str_to_hexa(char *str);
int			ft_abs(int nb);

#endif