/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:07:31 by yannis            #+#    #+#             */
/*   Updated: 2025/02/06 13:17:58 by ynzue-es         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	int			altitude;
	int			total_line;
	int			total_column;
	char		*filename;
}				t_data_img;

typedef struct s_data_points
{
	int			x;
	int			y;
	int			z;
	int			iso_x;
	int			iso_y;
	int			iso_x_next;
	int			iso_y_next;
	int			offset_x;
	int			offset_y;
	int			d_px;
}				t_data_points;

typedef struct s_segment_points
{
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			delta_x;
	int			delta_y;
	int			sign_x;
	int			sign_y;
	int			decision;
	long int	color;
}				t_segment_points;

typedef struct s_lines
{
	char		*line;
	char		**split_line;
	char		*next_line;
}				t_lines;

void			my_mlx_pixel_put(t_data_img *img, int x, int y, int color);
long int		str_to_hexa(char *str);
int				ft_abs(int nb);
int				close_window(t_data_img *img);
int				close_window_escape(int keycode, t_data_img *img);
void			free_split(char **spl);
int				size_parsing(char *filename, t_data_img *img);
void			iso_projection(int x, int y, int z, t_data_points *data_points);
void			iso_next_projection(int x, int y, int z,
					t_data_points *data_points);
int				calc_z(char *line_element, long int *color);
void			offset_points(t_segment_points *seg_points,
					t_data_points *data_points);
void			decision_loop_one(t_segment_points *seg_points, t_data_img *img,
					int color);
void			decision_loop_two(t_segment_points *seg_points, t_data_img *img,
					int color);
void			segment_plot(t_segment_points *seg_points, t_data_img *img,
					int color);
void			find_end_points(t_data_points *data_points, t_data_img *img,
					t_segment_points *seg_points, char **split_line);
int				find_next_end_points(t_data_points *data_points,
					t_data_img *img, t_segment_points *seg_points,
					char *next_line);
void			mini_segments(t_data_points *data_points,
					t_segment_points *seg_points, t_data_img *img,
					t_lines *lines);
void			change_lines(t_lines *lines);
int				split_line_and_next(t_lines *lines, int fd, t_data_img *img,
					int y);

#endif