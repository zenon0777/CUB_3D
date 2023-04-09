/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_engine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 15:25:04 by adaifi            #+#    #+#             */
/*   Updated: 2023/04/09 05:02:41 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_line_dir(t_data *data, t_player *player)
{
	double	x;
	double	y;
	int		step;
	int		i;

	x = data->short_dis_x;
	y = data->short_dis_y;
	i = 0;
	double dx = x - player->p_x;
	double dy = y - player->p_y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	double x_inc = dx / step;
	double y_inc = dy / step;
	x = player->p_x;
	y = player->p_y;
	while (i < step)
	{
		d_mlx_put_pixel(data, x, y, 0xFF0000);
		x += x_inc;
		y += y_inc;
		i++;
	}
}

void	cast_ray(t_data *data)
{
	double	colum;
	double	ang_inc;
	double	f_ray;
	int		flag;

	ang_inc = data->player.fov / data->width;
	f_ray = data->player.rotation_angle - (data->player.fov / 2);
	data->projection_plane_dis = (data->width / 2) / \
	tan(data->player.fov / 2);
	colum = 0;
	while (colum < data->width)
	{
		if (colum == 120)
		{
			f_ray = normalize_angle(f_ray);
			orizontios_hit(data, f_ray);
			sichoucu_hit(data, f_ray);
			flag = calc_dis(data);
			printf("short_dis == %f\n", data->short_dis);
			data->short_dis *= cos(data->player.rotation_angle - f_ray);
			//textures(data->textures, f_ray, flag);
			//rendering_wall(data, colum, flag);
			draw_line_dir(data, &data->player);
			f_ray += ang_inc;
		}
		colum++;
	}
}

void	draw_player(t_data *data)
{
	double	rad;
	double	step;
	double	x1;
	double	y1;

	rad = 5;
	x1 = data->player.p_x;
	y1 = data->player.p_y;
	step = data->player.walking_dir * data->player.move_speed;
	if (data->flag_dir == 1)
	{
		x1 += step * sin(data->player.rotation_angle);
		y1 -= step * cos(data->player.rotation_angle);
	}
	else
	{
		x1 += step * cos(data->player.rotation_angle);
		y1 += step * sin(data->player.rotation_angle);
	}
	wall_coloision(data, x1, y1);
	cast_ray(data);
	data->player.p_x -= data->x + TILE / 2;
	data->player.p_y -= data->y + TILE / 2;
}

void	wall_coloision(t_data *data, double x1, double y1)
{
	int	i1;
	int	j1;
	int	i;
	int	j;

	i = (int)floor(y1 / (double)TILE) + data->map->index;
	j = (int)floor(x1 / (double)TILE);
	i1 = (int)floor(data->player.p_y / (double)TILE) + data->map->index;
	j1 = (int)floor(data->player.p_x / (double)TILE);
	if (data->map->map_input[i1][j] != '1' && data->map->map_input[i][j1] != '1'
		&& data->map->map_input[i][j] != '1')
	{
		data->player.p_x = x1;
		data->player.p_y = y1;
	}
}
