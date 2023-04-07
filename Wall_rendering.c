/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:37:20 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/06 17:10:14 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	rendering_wall(t_data *data, int colum, int flag)
{
	double			i;
	double			j;
	unsigned int	color;

	data->real_pwh = (TILE / data->short_dis) * data->projection_plane_dis;
	if (data->real_pwh > data->screen_height)
		data->pwh = data->screen_height;
	else
		data->pwh = data->real_pwh;
	i = colum;
	j = (data->screen_height / 2) - (data->pwh / 2);
	data->begin = (data->screen_height / 2) - (data->real_pwh / 2);
	while (j < data->pwh + ((data->screen_height / 2) - (data->pwh / 2)))
	{
		color = texture_mapping(data, flag, j);
		d_mlx_put_pixel(data, i, j, color);
		j++;
	}
}

int	calc_dis(t_data *data)
{
	double	hor_dis;
	double	ver_dis;

	hor_dis = sqrt((data->player.p_x - data->gridhor_x) * \
	(data->player.p_x - data->gridhor_x) + (data->player.p_y \
	- data->gridhor_y) * (data->player.p_y - data->gridhor_y));
	ver_dis = sqrt((data->player.p_x - data->gridver_x) * \
	(data->player.p_x - data->gridver_x) +(data->player.p_y - \
	data->gridver_y) * (data->player.p_y - data->gridver_y));
	if (data->player.p_x == data->gridver_x)
	{
		data->short_dis_x = data->gridhor_x;
		data->short_dis_y = data->gridhor_y;
		data->short_dis = hor_dis;
		return (HOR);
	}
	else if (data->player.p_x == data->gridhor_x)
	{
		data->short_dis_x = data->gridver_x;
		data->short_dis_y = data->gridver_y;
		data->short_dis = ver_dis;
		return (VER);
	}
	return (short_dis(data, hor_dis, ver_dis));
}

int	short_dis(t_data *data, double hor_dis, double ver_dis)
{
	if (hor_dis <= ver_dis)
	{
		data->short_dis_x = data->gridhor_x;
		data->short_dis_y = data->gridhor_y;
		data->short_dis = hor_dis;
		return (HOR);
	}
	else if (hor_dis > ver_dis)
	{
		data->short_dis_x = data->gridver_x;
		data->short_dis_y = data->gridver_y;
		data->short_dis = ver_dis;
		return (VER);
	}
	return (3);
}
