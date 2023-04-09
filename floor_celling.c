/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_celling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:14:59 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 03:21:03 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

void	celling_draw(t_data *data)
{
	int		c_color;
	int		mid_point;
	double	x;
	double	y;

	c_color = (data->map->c_color->red << 16) + \
		(data->map->c_color->green << 8) + data->map->c_color->blue;
	mid_point = data->height / 2;
	y = 0;
	while (y <= mid_point)
	{
		x = 0;
		while (x < data->width)
		{
			d_mlx_put_pixel(data, x, y, c_color);
			x++;
		}
		y++;
	}
	floor_draw(data, y, mid_point);
}

void	floor_draw(t_data *data, int y, int mid_point)
{
	int	f_color;
	int	x;

	f_color = (data->map->f_color->red << 16) + \
		(data->map->f_color->green << 8) + data->map->f_color->blue;
	while (y > mid_point && y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			d_mlx_put_pixel(data, x, y, f_color);
			x++;
		}
		y++;
	}
}
